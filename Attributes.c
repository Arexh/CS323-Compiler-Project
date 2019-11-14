#include "HashTable.c"
#include "ASTNode.c"

typedef struct FunctionAttribute {
    char *returnType;
    char *ID;
    HashTable *hashTable;
} FunctionAttribute;

FunctionAttribute *new_function_attribute(char *returnType, char *ID) {
    FunctionAttribute *attribute = (FunctionAttribute *)malloc(sizeof(FunctionAttribute));
    attribute->returnType = returnType;
    attribute->ID = ID;
    attribute->hashTable = new_hash_table();
    return attribute;
}

FunctionAttribute *put_function(HashTable *table, char *returnType, char *ID) {
    printf("returnType: %s\n", returnType);
    printf("ID: %s\n", ID);
    FunctionAttribute *attribute = new_function_attribute(returnType, ID);
    // put function into symbol table
    hash_table_put(table, ID, "function", attribute);
    return attribute;
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

void put_para(FunctionAttribute *attribute, ASTNode *specifier, ASTNode *varDec) {
    // specifier: TYPE | StructSpecifier
    ASTNode *specifierChild = specifier->child[0];
    char *type;
    char *id;
    if (strcmp(specifierChild->type, "TYPE") == 0) {
        type = specifierChild->value;
    } else {
        // StructSpecifier, not allowed, print error
        printf("Error type 16 at Line %d: struct parameter is not allowed\n", specifierChild->row);
        return;
    }
    // varDec: ID | VarDec LB INT RB
    if (varDec->child_count == 1) {
        // ID
        id = varDec->child[0]->value;
        hash_table_put(attribute->hashTable, id, type, NULL);
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
        ArrayAttribute *attribtue = new_array_attribute(type, dimension);
        hash_table_put(attribute->hashTable, id, "array", attribute);
        // TableItem *item = hash_table_get(attribute->hashTable, id);
        // printf("ID %s, TYPE: %s, Atype: %s\n", item->ID, item->type, ((ArrayAttribute *)item->attribute)->type);
        // printf("arrType, id: %s, dimension: %d, type: %s\n", id, dimension, type);
    }
}