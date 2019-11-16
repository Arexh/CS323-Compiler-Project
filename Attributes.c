#include "ASTNode.c"
#include "SymbolTable.c"
#include "Struct.c"

struct FunctionAttribute *currentFunction;
int currentScopeNumber;

typedef struct FunctionAttribute {
    char *returnType;
    char *ID;
    HashTable *hashTable;
    struct FunctionAttribute *next;
} FunctionAttribute;

FunctionAttribute *new_function_attribute(char *returnType, char *ID) {
    FunctionAttribute *attribute = (FunctionAttribute *)malloc(sizeof(FunctionAttribute));
    attribute->returnType = returnType;
    attribute->ID = ID;
    attribute->hashTable = new_hash_table();
    attribute->next = NULL;
    return attribute;
}

// 0: not initialized, 1: initialize, -1: ID already used
int scope_check(HashTable *hashTable, char *ID, char *type) {
    TableItem *item = hash_table_get(hashTable, ID);
    if (item == NULL) {
        return 0;
    }
    while(item) {
        if (strcmp(item->ID, ID) == 0 && currentScopeNumber == item->scopeNum) {
            if (strcmp(item->type, type) == 0) {
                return 1;
            } else {
                if (strcmp(type, "struct") && strcmp(item->type, "struct")) {
                    return -1;
                }
            }
        }
        item = item->next;
    }
    return 0;
}

int struct_scope_check(HashTable *hashTable, char *ID) {
    return scope_check(hashTable, ID, "struct");
}

int function_scope_check(HashTable *hashTable, char *ID) {
    return scope_check(hashTable, ID, "function");
}

int variable_scope_check(HashTable *hashTable, char *ID, char *type) {
    return scope_check(hashTable, ID, type);
}

void function_stack_push(ASTNode *specifier, char *ID, int IDLineNo) {
    int check = function_scope_check(currentTable, ID);
    if (check == 1) {
        printf("Error type 4 at Line %d: function is redeﬁned\n", IDLineNo);
    } else if (check == -1) {
        printf("Error type 21 at Line %d: function ID is already used by a variable.\n", IDLineNo);
    }
    FunctionAttribute *attribute;
    if (specifier->child_count == 0) {
        // TYPE
        char *returnType = specifier->value;
        attribute = new_function_attribute(returnType, ID);
        // put function into symbol table
        hash_table_put(currentTable, ID, "function", attribute, currentScopeNumber);
    } else if (specifier->child_count == 2) {
        // STRUCT ID, scope check
        char *StructID = specifier->child[1]->value;
        int check = struct_scope_check(currentTable, StructID);
        if (check == 0) {
            // struct is not defined, print error
            printf("Error type 15 at Line %d: struct is used without deﬁnition\n", specifier->child[1]->row);
            attribute = new_function_attribute("error", ID);
        } else if (check == 1) {
            // returnType = struct ID
            attribute = new_function_attribute(specifier->child[1]->value, ID);
            hash_table_put(currentTable, ID, "function", attribute, currentScopeNumber);
        } else if (check == -1) {
            printf("Error type 19 at Line %d: use variable as struct ID\n", specifier->child[1]->row);
            attribute = new_function_attribute("error", ID);
        }
    } else {
        // declare strunct is not allowed, print error
        printf("Error type 17 at Line %d: declare struct in function specifier is not allowed\n", specifier->child[0]->row);
        attribute = new_function_attribute("error", ID);
    }
    if (attribute) {
        if (currentFunction) {
            attribute->next = currentFunction;
            currentFunction = attribute;
        } else {
            currentFunction = attribute;
        }
    }
}

void function_stack_pop() {
    currentFunction = currentFunction->next;
}

typedef struct TypeArrayAttribute {
    char *type;
    int dimension;
} TypeArrayAttribute;

TypeArrayAttribute *new_type_array_attribute(char *type, int dimension) {
    TypeArrayAttribute *attribute = (TypeArrayAttribute *)malloc(sizeof(TypeArrayAttribute));
    attribute->type = type;
    attribute->dimension = dimension;
    return attribute;
}

StructAttribute *put_struct_specifier(ASTNode *specifier) {
    // STRUCT ID LC DefList RC
    ASTNode *defList = specifier->child[3];
    StructAttribute *structAttribute;
    char *structID = specifier->child[1]->value;
    if (strcmp(defList->type, "NONE")) {
        int varNum = *((int *)specifier->child[3]->value);
        structAttribute = new_struct_attribute(varNum);
        int index = 0;
        while(strcmp(defList->type, "NONE")) {
            ASTNode *def = defList->child[0];
            char *specifier;
            char *specifierType = def->child[0]->child[0]->type;
            char *insideStructID;
            TableItem *structItem;
            if (strcmp(specifierType, "TYPE") == 0) {
                // TYPE
                specifier = def->child[0]->child[0]->value;
            } else {
                // StructSpecifier
                specifier = "struct";
                ASTNode *structSpecifier = def->child[0]->child[0];
                if (structSpecifier->child_count == 5) {
                    printf("Error at Line %d: declare a struct inside another struct is not allowed\n", structSpecifier->row);
                } else {
                    insideStructID = structSpecifier->child[1]->value;
                    if (strcmp(insideStructID, structID)) {
                        structItem = find_struct(currentTable, insideStructID);
                        if (structItem == NULL) {
                            printf("Error at Line %d: undifined struct \"%s\"\n", structSpecifier->row, insideStructID);
                            defList = defList->child[1];
                            continue;
                        }
                    }
                }
            }
            ASTNode *decList = def->child[1];
            while(1) {
                ASTNode *dec = decList->child[0];
                if (dec->child_count == 3) {
                    printf("Error at Line %d: assignment in struct is not allowed\n", dec->row);
                } else {
                    ASTNode *varDec = dec->child[0];
                    int dimension = 0;
                    while (varDec->child_count == 4) {
                        varDec = varDec->child[0];
                        dimension++;
                    }
                    StructVariable *var = new_struct_variable();
                    var->type = specifier;
                    var->ID = varDec->child[0]->value;
                    var->dimension = dimension;
                    if (strcmp(specifier, "struct") == 0) {
                        var->structID = insideStructID;
                        if (strcmp(insideStructID, structID) == 0) {
                            var->attribute = structAttribute;
                        } else {
                            var->attribute = structItem->attribute;
                        }
                    }
                    structAttribute->varDec[index++] = var;
                }
                if (decList->child_count == 1) {
                    break;
                }
                decList = decList->child[2];
            }
            defList = defList->child[1];
        }
    } else {
        structAttribute = new_struct_attribute(0);
    }
    int result = variable_scope_check(currentTable, structID, "struct");
    if (result == 1) {
        printf("Error type 15 at Line %d: redeﬁne the same structure type\n", specifier->row);
    } else {
        sort_struct_attribute_varDec(structAttribute);
        hash_table_put(currentTable, structID, "struct", structAttribute, currentScopeNumber);
    }
    return structAttribute;
}

void put_para_or_var(ASTNode *specifier, ASTNode *varDec, int para) {
    char *ID;
    int dimension = 0;
    if (varDec->child_count == 1) {
        // ID
        ID = varDec->child[0]->value;
    } else {
        // VarDec LB INT RB
        ASTNode *node = varDec->child[0];
        while(node->child_count == 4) {
            dimension++;
            node = node->child[0];
        }
        ID = node->child[0]->value;
    }
    char *type;
    StructAttribute *structAttribute;
    // specifier: TYPE | StructSpecifier
    if (strcmp(specifier->type, "TYPE") == 0) {
        type = specifier->value;
    } else {
        // StructSpecifier: STRUCT ID LC DefList RC | STRUCT ID
        if (specifier->child_count == 2) {
            char *structID = specifier->child[1]->value;
            // STRUCT ID
            int result = struct_scope_check(currentTable, structID);
            if (result == 0) {
                printf("Error at Line %d: undifined struct \"%s\"\n", specifier->row, structID);
                return;
            }
        } else {
            // STRUCT ID LC DefList RC
            if (para == 1) {
                printf("Error at Line %d: define struct before parameter is not allowed\n", specifier->row);
                return;
            } else {
                type = "structVariable";
                structAttribute = put_struct_specifier(specifier);
            }
        }
    }
    int result = variable_scope_check(currentTable, ID, type);
    if (result == -1 || result == 1) {
        // already been used
        if (para) {
            printf("Error at Line %d: parameter is redifined in the same function\n", varDec->row);
        } else {
            printf("Error type 3 at Line %d: variable is redeﬁned in the same scope\n", varDec->row);
        }
    } else if (result == 0) {
        if (strcmp(type, "structVariable") == 0) {
            // put struct here
            StructVariableAttribute *structVariableAttribute = new_struct_variable_attribute();
            structVariableAttribute->dimension = dimension;
            structVariableAttribute->structAttribute = structAttribute;
            hash_table_put(currentTable, ID, "structVariable", structVariableAttribute, currentScopeNumber);
        } else {
            // put variable here
            if (dimension) {
                TypeArrayAttribute *attribute = new_type_array_attribute(type, dimension);
                hash_table_put(currentTable, ID, "array", attribute, currentScopeNumber);
            } else {
                hash_table_put(currentTable, ID, type, NULL, currentScopeNumber);
            }
        }
    }
}

void put_var(ASTNode *currentSpecifier, ASTNode *varDec) {
    put_para_or_var(currentSpecifier, varDec, 0);
}

void put_para(ASTNode *specifier, ASTNode *varDec) {
    put_para_or_var(specifier, varDec, 1);
}

void add_into_symbol_table(HashTable *hashTable, SymbolTable *symbolTable, ASTNode *newNode) {
    char *ID = newNode->child[0]->child[0]->value;
    // symbol_table_add_node(hashTable, symbolTable, newNode->);
}

void add_into_hash_table(HashTable *hashTable, ASTNode *newNode) {

}

void *get_attribute(ASTNode *node) {
    if (strcmp(node->child[1]->type, "DecList") == 0) {
        // SpecifierTrigger DecList SEMI

    } else {

    }
}

void assign_type_check(ASTNode *specifier, ASTNode *exp) {

}
