#include "HashTable.c"

typedef struct SymbolTable {
    struct VariableNode *node;
    struct VariableNode *last;
} SymbolTable;

typedef struct VariableNode {
    struct ListNode *node;
    struct VariableNode *next;
} VariableNode;

SymbolTable *new_symbol_table() {
    SymbolTable *symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));
    symbolTable->node = NULL;
    symbolTable->last = NULL;
}

VariableNode *new_variable_node() {
    VariableNode *node = (VariableNode *)malloc(sizeof(VariableNode));
    node->node = NULL;
    node->next = NULL;
}

void free_symbol_table(SymbolTable *table) {
    if (table) {
        table->node = NULL;
        table->last = NULL;
        free(table);
    }
}

void free_varible_node(VariableNode *variableNode) {
    if (variableNode) {
        if (variableNode->node) {
            free_list_node(variableNode->node);
            variableNode->node = NULL;
        }
        if (variableNode->next) {
            variableNode->next = NULL;
        }
    }
    free(variableNode);
}

void add_table_list(SymbolTable *table, VariableNode *node) {
    if (table->node == NULL) {
        table->last = node;
        table->node = node;
    } else {
        table->last->next = node;
        table->last = node;
    }
}

void printf_table_list(SymbolTable *table) {
    VariableNode *node = table->node;
    int i = 0;
    while(node) {
        printf("node%d, name: %s, attribute%s.\n", i++, node->node->name, node->node->attribute);
        node = node->next;
    }
}

void symbol_table_add_node(HashTable *hashTable, SymbolTable *symbolTable, char* name, char* attribute) {
    int index = hash_function_pjw(name);
    ListNode *node = hash_table_put(hashTable, name, attribute);
    if (node == NULL) {
        printf("ListNode is NULL!\n");
    }
    VariableNode *variableNode = new_variable_node();
    variableNode->node = node;
    add_table_list(symbolTable, variableNode);
}

void symbol_table_remove(HashTable *hashTable, SymbolTable *symbolTable) {
    VariableNode *variableNode = symbolTable->node;
    while (variableNode) {
        ListNode *node = variableNode->node;
        int index = hash_function_pjw(node->name);
        if (node->previous) {
            node->previous->next = node->next;
            if (node->next) {
                node->next->previous = node->previous;
            }
        } else {
            hashTable->table[index] = node->next;
            if (node->next) {
                node->next->previous = NULL;
            }
        }
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
//     symbol_table_add_node(hashTable, symbolTable, "111", "101");
//     symbol_table_add_node(hashTable, symbolTable, "222", "202");
//     symbol_table_add_node(hashTable, symbolTable, "333", "303");
//     symbol_table_add_node(hashTable, symbolTable1, "333", "1213");
//     symbol_table_add_node(hashTable, symbolTable1, "333", "321321");
//     symbol_table_remove(hashTable, symbolTable1);
//     ListNode *node = hashTable->table[hash_function_pjw("333")];
//     printf("%s", node->attribute);
//     puts("HERE");
// }