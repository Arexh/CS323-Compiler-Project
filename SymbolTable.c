struct SymbolTable *currentSymbolTable;
struct LoopStack *currentLoop;

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

typedef struct LoopStack {
    struct LoopStack *next;
} LoopStack;

LoopStack *new_loop_stack() {
    LoopStack *newLoop = (LoopStack *)malloc(sizeof(LoopStack));
    newLoop->next = NULL;
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

TableItem *symbol_table_add_node(HashTable *hashTable, SymbolTable *symbolTable, char* ID, char* type, void *attribute, int scopeNum, int dimension, int *dimensions) {
    int index = hash_function_pjw(ID);
    TableItem *item = hash_table_put(hashTable, ID, type, attribute, scopeNum, dimension, dimensions);
    VariableNode *variableNode = new_variable_node();
    variableNode->item = item;
    add_table_list(symbolTable, variableNode);
    return item;
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
