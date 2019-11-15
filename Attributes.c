#include "ASTNode.c"
#include "SymbolTable.c"

struct FunctionAttribute *currentFunction;

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

// 0: not initialized, 1: initialize, -1: ID already used by variable
int struct_scope_check(HashTable *hashTable, ASTNode *structSpecifier) {
    char *ID = structSpecifier->child[1]->value;
    TableItem *item = hash_table_get(hashTable, ID);
    if (item == NULL) {
        return 0;
    }
    while(item) {
        if(strcmp(item->ID, ID) == 0) {
            if(strcmp(item->type, "struct") == 0) {
                return 1;
            } else {
                printf("Error type 19 at Line %d: use variable as struct ID\n", structSpecifier->child[0]->row);
                return -1;
            }
        }
        item = item->next;
    }
    return 0;
}

void function_stack_push(ASTNode *specifier, char *ID) {
    printf("push function %s.\n", ID);
    FunctionAttribute *attribute;
    if (specifier->child_count == 0) {
        // TYPE
        char *returnType = specifier->value;
        attribute = new_function_attribute(returnType, ID);
        // put function into symbol table
        hash_table_put(currentTable, ID, "function", attribute);
    } else if(specifier->child_count == 2) {
        // STRUCT ID, scope check
        int check = struct_scope_check(currentTable, specifier);
        if (check == 0) {
            // struct is not defined, print error
            printf("Error type 15 at Line %d: struct is used without deﬁnition\n", specifier->row);
        } else if(check == 1) {
            // returnType = struct ID
            attribute = new_function_attribute(specifier->child[1]->value, ID);
            hash_table_put(currentTable, ID, "function", attribute);
        }
    } else {
        // declare strunct is not allowed, print error
        printf("Error type 17 at Line %d: declare struct in function specifier is not allowed\n", specifier->child[0]->row);
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
    printf("pop function %s.\n", currentFunction->ID);
    currentFunction = currentFunction->next;
}

typedef struct ArrayAttribute {
    char *type;
    int dimension;
} ArrayAttribute;

ArrayAttribute *new_array_attribute(char *type, int dimension) {
    ArrayAttribute *attribute = (ArrayAttribute *)malloc(sizeof(ArrayAttribute));
    attribute->type = type;
    attribute->dimension = dimension;
    return attribute;
}

void put_para(ASTNode *specifier, ASTNode *varDec) {
    // specifier: TYPE | StructSpecifier
    ASTNode *specifierChild = specifier->child[0];
    char *type;
    char *id;
    if (strcmp(specifierChild->type, "TYPE") == 0) {
        type = specifierChild->value;
    } else {
        // StructSpecifier, not allowed, print error
        printf("Error type 18 at Line %d: struct parameter is not allowed\n", specifierChild->row);
        return;
    }
    // varDec: ID | VarDec LB INT RB
    if (varDec->child_count == 1) {
        // ID
        id = varDec->child[0]->value;
        hash_table_put(currentTable, id, type, NULL);
        // printf("rType, id: %s, type: %s\n", id, type);
    } else {
        // VarDec LB INT RB
        int dimension = 1;
        ASTNode *node = varDec->child[0];
        while(node->child_count == 4) {
            dimension++;
            node = node->child[0];
        }
        id = node->child[0]->value;
        ArrayAttribute *attribute = new_array_attribute(type, dimension);
        hash_table_put(currentTable, id, "array", attribute);
        // TableItem *item = hash_table_get(attribute->hashTable, id);
        // printf("ID %s, TYPE: %s, Atype: %s\n", item->ID, item->type, ((ArrayAttribute *)item->attribute)->type);
        // printf("arrType, id: %s, dimension: %d, type: %s\n", id, dimension, type);
    }
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

void variable_scope_check() {

}

void new_dec(int scopeNum, HashTable *table, SymbolTable *symbolTable, ASTNode *specifier, ASTNode *newNode) {
    // // add dec into hashTable
    // if (temporaryScope->scopeNum) {
    //     // temporary scope
    //     add_into_symbol_table(currentTable, currentSymbolTable, newNode);
    // } else {
    //     // function scope
    //     add_into_hash_table(currentTable, newNode);
    // }
}