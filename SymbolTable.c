#include "HashTable.c"

typedef struct SymbolTable {
    struct VariableNode *first;
    struct VariableNode *last;
    struct SymbolTable *next;
} SymbolTable;

typedef struct VariableNode {
    struct TableItem *item;
    struct VariableNode *next;
} VariableNode;

SymbolTable *new_symbol_table() {
    SymbolTable *symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));
    symbolTable->first = NULL;
    symbolTable->last = NULL;
    symbolTable->next = NULL;
}

VariableNode *new_variable_node() {
    VariableNode *node = (VariableNode *)malloc(sizeof(VariableNode));
    node->item = NULL;
    node->next = NULL;
}

void free_symbol_table(SymbolTable *table) {
    if (table) {
        table->first = NULL;
        table->last = NULL;
        free(table);
    }
}

void free_varible_node(VariableNode *variableNode) {
    if (variableNode) {
        if (variableNode->item) {
            free_table_item(variableNode->item);
            variableNode->item = NULL;
        }
        if (variableNode->next) {
            variableNode->next = NULL;
        }
    }
    free(variableNode);
}

void add_table_list(SymbolTable *table, VariableNode *node) {
    if (table->first == NULL) {
        table->last = node;
        table->first = node;
    } else {
        table->last->next = node;
        table->last = node;
    }
}

void printf_table_list(SymbolTable *table) {
    VariableNode *node = table->first;
    int i = 0;
    while(node) {
        printf("node%d, ID: %s, type:%s.\n", i++, node->item->ID, node->item->type);
        node = node->next;
    }
}

void symbol_table_add_node(HashTable *hashTable, SymbolTable *symbolTable, char* ID, char* type, void *attribute) {
    int index = hash_function_pjw(ID);
    TableItem *item = hash_table_put(hashTable, ID, type, attribute);
    VariableNode *variableNode = new_variable_node();
    variableNode->item = item;
    add_table_list(symbolTable, variableNode);
}

void symbol_table_remove(HashTable *hashTable, SymbolTable *symbolTable) {
    VariableNode *variableNode = symbolTable->first;
    while (variableNode) {
        TableItem *item = variableNode->item;
        hash_table_remove(hashTable, item);
        VariableNode *temp = variableNode;
        variableNode = variableNode->next;
        free_varible_node(temp);
    }
    free_symbol_table(symbolTable);
}

// int main() {
//     SymbolTable *symbolTable = new_symbol_table();
//     SymbolTable *symbolTable1 = new_symbol_table();
//     HashTable *hashTable = new_hash_table();
//     symbol_table_add_node(hashTable, symbolTable, "111", "101", NULL);
//     symbol_table_add_node(hashTable, symbolTable, "222", "202", NULL);
//     symbol_table_add_node(hashTable, symbolTable, "333", "303", NULL);
//     symbol_table_add_node(hashTable, symbolTable1, "333", "1213", NULL);
//     symbol_table_add_node(hashTable, symbolTable1, "333", "321321", NULL);
//     symbol_table_remove(hashTable, symbolTable1);
//     TableItem *node = hashTable->table[hash_function_pjw("333")];
//     printf("%s\n", node->next->type);
//     puts("HERE");
// }