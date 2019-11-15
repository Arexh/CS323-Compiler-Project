#include "ASTNode.c"
#include "SymbolTable.c"

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

typedef struct StructAttribute {
    void *varDec;
    int varNum;
    int dimension;
} StructAttribute;

StructAttribute *new_struct_attribute() {
    StructAttribute *attribute = (StructAttribute *)malloc(sizeof(StructAttribute));
    attribute->varDec = NULL;
    attribute->varNum = 0;
    attribute->dimension = 0;
    return attribute;
}

char *get_varDec_ID(ASTNode *varDec) {
    // varDec-> ID | VarDec LB INT RB
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
    return ID;
}

void put_para_or_var(ASTNode *specifier, ASTNode *varDec, int para) {
    char *ID = get_varDec_ID(varDec);
    char *type;
    // specifier: TYPE | StructSpecifier
    if (strcmp(specifier->type, "TYPE") == 0) {
        type = specifier->value;
    } else {
        // StructSpecifier: STRUCT ID LC DefList RC | STRUCT ID
        if (specifier->child_count == 2) {
            // STRUCT ID
            char *structID = specifier->child[1]->value;
            int result = struct_scope_check(currentTable, structID);
            if (result == 0) {
                
            } else {

            }
        } else {
            // STRUCT ID LC DefList RC
            if (para == 1) {
                printf("Error type 18 at Line %d: define struct before parameter is not allowed\n", specifier->row);
            } else {
                
            }
        }
        type = "struct";
    }
    int result = variable_scope_check(currentTable, ID, type);
    if (result == -1) {
        // already been used
        if (strcmp(type, "struct") == 0) {
            
        } else {
            if (para) {
                printf("Error type 20 at Line %d: parameter is redifined in the same function\n", varDec->row);
            } else {
                printf("Error type 3 at Line %d: variable is redeﬁned in the same scope\n", varDec->row);
            }
        }
    }
    if (strcmp(type, "struct") == 0) {
        // put struct here
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
