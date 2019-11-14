#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 0x3FFF

/* retrieve from https://blog.csdn.net/smstong/article/details/51145786 */
typedef struct TableItem {
    char *name;
    char *type;
    void *attribute;
    struct TableItem *next;
    struct TableItem *previous;
} TableItem;

typedef struct HashTable {
    TableItem ** table;
} HashTable;

HashTable *new_hash_table() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (TableItem **)malloc(sizeof(TableItem *) * TABLE_SIZE);
    memset(hashTable->table, 0, sizeof(TableItem *) * TABLE_SIZE);
    return hashTable;
}

TableItem *new_table_item(char *name, char *type, void *attribute) {
    TableItem *item = (TableItem *)malloc(sizeof(TableItem));
    item->name = name;
    item->type = type;
    item->attribute = attribute;
    item->next = NULL;
    item->previous = NULL;
    return item;
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

TableItem *hash_table_put(HashTable *hashTable, char *name, char *type, void *attribute) {
    int index = hash_function_pjw(name) % TABLE_SIZE;
    TableItem *item = hashTable->table[index];
    TableItem *newItem = new_table_item(name, type, attribute);
    if (item) {
        if (strcmp(item->name, name) == 0) {
            hashTable->table[index] = newItem;
            newItem->next = item;
            item->previous = newItem;
        } else {
            TableItem *temp = item;
            item = item->next;
            while(item) {
                if (strcmp(item->name, name) == 0) {
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

TableItem *hash_table_get(HashTable *hashTable, char *name) {
    int index = hash_function_pjw(name) % TABLE_SIZE;
    TableItem *item = hashTable->table[index];
    if (item == NULL) {
        return NULL;
    }
    if (strcmp(item->name, name) == 0) {
        return item;
    } else {
        item = item->next;
        while(item) {
            if (strcmp(item->name, name) == 0) {
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
    if(previous) {
        previous->next = next;
        if(next) {
            next->previous = previous;
        }
    } else {
        int index = hash_function_pjw(item->name) % TABLE_SIZE;
        if(next) {
            hashTable->table[index] = next;
            next->previous = NULL;
        } else {
            hashTable->table[index] = NULL;
        }
    }
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
//     // ListNode *node = new_list_node("name", "attribute");
//     // printf("node_ind: %lld\n", node);
//     // memcpy(pointer, &type, sizeof(char *));
//     // memcpy(pointer + sizeof(char *), &node, sizeof(ListNode *));
//     // char *getType;
//     // memcpy(&getType, pointer, sizeof(char *));
//     // printf("getType: %lld\n", getType);
//     // ListNode *getNode;
//     // memcpy(&getNode, pointer + sizeof(char *), sizeof(ListNode *));
//     // printf("getNode: %lld\n", getNode);
//     // printf("%s\n", getNode->name);
//     puts("HERE");
// }