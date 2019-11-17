#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 0x3FFF

struct HashTable *currentTable;

/* https://blog.csdn.net/smstong/article/details/51145786 */
typedef struct TableItem {
    char *ID;
    char *type;
    void *attribute;
    int scopeNum;
    int dimension;
    struct TableItem *next;
    struct TableItem *previous;
} TableItem;

typedef struct HashTable {
    TableItem ** table;
    struct HashTable *next;
} HashTable;

HashTable *new_hash_table() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (TableItem **)malloc(sizeof(TableItem *) * TABLE_SIZE);
    hashTable->next = NULL;
    memset(hashTable->table, 0, sizeof(TableItem *) * TABLE_SIZE);
    return hashTable;
}

TableItem *new_table_item(char *ID, char *type, void *attribute, int scopeNum, int dimension) {
    TableItem *item = (TableItem *)malloc(sizeof(TableItem));
    item->ID = ID;
    item->type = type;
    item->attribute = attribute;
    item->next = NULL;
    item->previous = NULL;
    item->scopeNum = scopeNum;
    item->dimension = dimension;
    return item;
}

void free_table_item(TableItem *item) {
    if (item) {
        item->ID = NULL;
        item->type = NULL;
        item->attribute = NULL;
        item->next = NULL;
        item->previous = NULL;
    }
    free(item);
}

void free_hash_table(HashTable *hashTable) {
    if (hashTable) {
        if (hashTable->table) {
            int i = 0;
            for (i = 0; i < TABLE_SIZE; i++) {
                hashTable->table[i] = NULL;
            }
            free(hashTable->table);
            hashTable->table = NULL;
        }
        free(hashTable);
    }
}

void hash_table_stack_push() {
    HashTable *newTable = new_hash_table();
    newTable->next = currentTable;
    currentTable = newTable;
}

HashTable *hash_table_stack_pop() {
    currentTable = currentTable->next;
}

unsigned int hash_function_pjw(char* key) {
    unsigned int val = 0, i;
    for (; *key; ++key) {
        val = (val << 2) + *key;
        if (i = val & ~TABLE_SIZE) {
            val = (val ^ (i >> 12)) & TABLE_SIZE;
        }
    }
    return val;
}

TableItem *hash_table_put(HashTable *hashTable, char *ID, char *type, void *attribute, int scopeNum, int dimension) {
    int index = hash_function_pjw(ID) % TABLE_SIZE;
    TableItem *item = hashTable->table[index];
    TableItem *newItem = new_table_item(ID, type, attribute, scopeNum, dimension);
    if (item) {
        if (strcmp(item->ID, ID) == 0) {
            hashTable->table[index] = newItem;
            newItem->next = item;
            item->previous = newItem;
        } else {
            TableItem *temp = item;
            item = item->next;
            while(item) {
                if (strcmp(item->ID, ID) == 0) {
                    temp->next = newItem;
                    newItem->previous = temp;
                    newItem->next = item;
                    item->previous = newItem;
                    return newItem;
                }
                temp = item;
                item = item->next;
            }
            temp->next = newItem;
            newItem->previous = temp;
        }
    } else {
        hashTable->table[index] = newItem;
    }
    return newItem;
}

TableItem *hash_table_get(HashTable *hashTable, char *ID) {
    int index = hash_function_pjw(ID) % TABLE_SIZE;
    TableItem *item = hashTable->table[index];
    if (item == NULL) {
        return NULL;
    }
    if (strcmp(item->ID, ID) == 0) {
        return item;
    } else {
        item = item->next;
        while(item) {
            if (strcmp(item->ID, ID) == 0) {
                return item;
            }
            item = item->next;
        }
        return NULL;
    }
}

void hash_table_remove(HashTable *hashTable, TableItem *item) {
    TableItem *previous = item->previous;
    TableItem *next = item->next;
    if (previous) {
        previous->next = next;
        if (next) {
            next->previous = previous;
        }
    } else {
        int index = hash_function_pjw(item->ID) % TABLE_SIZE;
        if (next) {
            hashTable->table[index] = next;
            next->previous = NULL;
        } else {
            hashTable->table[index] = NULL;
        }
    }
}

TableItem *find_struct(HashTable *hashTable, char *ID) {
    HashTable *current = hashTable;
    while (current) {
        TableItem *item = hash_table_get(current, ID);
        while (item) {
            if (strcmp(item->ID, ID) == 0 && strcmp(item->type, "struct") == 0) {
                return item;
            }
            item = item->next;
        }
        current = current->next;
    }
    return NULL;
}

TableItem *find_variable(HashTable *hashTable, char *ID) {
    HashTable *current = hashTable;
    while (current) {
        TableItem *item = hash_table_get(current, ID);
        while (item) {
            if (strcmp(item->ID, ID) == 0 && strcmp(item->type, "struct")) {
                return item;
            }
            item = item->next;
        }
        current = current->next;
    }
    return NULL;
}

// int main() {
//     HashTable *hashTable = new_hash_table();
//     hashTable->table[9001] = new_table_item("test", "21312", NULL);
//     TableItem *node1 = hash_table_put(hashTable, "variable", "aaa", NULL);
//     TableItem *node2 = hash_table_put(hashTable, "variable", "bbb", NULL);
//     TableItem *node3 = hash_table_put(hashTable, "variable", "bbc", NULL);
//     TableItem *node = hash_table_get(hashTable, "variable");
//     hash_table_remove(hashTable, node3);
//     TableItem *get = hash_table_get(hashTable, "variable");
//     // void *pointer = malloc(sizeof(char *) + sizeof(ListNode *));
//     // memset(pointer, 0, sizeof(char *) + sizeof(ListNode *));
//     // char *type = "INT";
//     // printf("type_ind: %lld\n", type);
//     // ListNode *node = new_list_node("ID", "attribute");
//     // printf("node_ind: %lld\n", node);
//     // memcpy(pointer, &type, sizeof(char *));
//     // memcpy(pointer + sizeof(char *), &node, sizeof(ListNode *));
//     // char *getType;
//     // memcpy(&getType, pointer, sizeof(char *));
//     // printf("getType: %lld\n", getType);
//     // ListNode *getNode;
//     // memcpy(&getNode, pointer + sizeof(char *), sizeof(ListNode *));
//     // printf("getNode: %lld\n", getNode);
//     // printf("%s\n", getNode->ID);
//     puts("HERE");
// }