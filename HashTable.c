#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 0x3FFF

/* retrieve from https://blog.csdn.net/smstong/article/details/51145786 */

typedef struct HashTable {
    struct ListNode ** table;
} HashTable;

typedef struct ListNode {
    char *name;
    char *attribute;
    struct ListNode *next;
    struct ListNode *previous;
} ListNode;

HashTable *new_hash_table() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (ListNode **)malloc(sizeof(ListNode *) * TABLE_SIZE);
    memset(hashTable->table, 0, sizeof(ListNode *) * TABLE_SIZE);
    return hashTable;
}

ListNode *new_list_node(char *name, char *attribute) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    int len = strlen(name);
    node->name = name;
    node->attribute = attribute;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

void free_list_node(ListNode *node) {
    if (node) {
        node->next = NULL;
        node->previous = NULL;
        free(node);
    }
}

void free_hash_table(HashTable *hashTable) {
    if (hashTable) {
        if (hashTable->table) {
            int i = 0;
            for (i = 0; i < TABLE_SIZE; i++) {
                ListNode *node = hashTable->table[i];
                ListNode *next = NULL;
                while (node) {
                    next = node->next;
                    free_list_node(node);
                    node = next;
                }
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

ListNode *hash_table_put(HashTable *hashTable, char *name, char *attribute) {
    int index = hash_function_pjw(name) % TABLE_SIZE;
    ListNode *node = hashTable->table[index];
    ListNode *addNode = new_list_node(name, attribute);
    if (node) {
        if (strcmp(node->name, name) == 0) {
            hashTable->table[index] = addNode;
            addNode->next = node;
            node->previous = addNode;
            addNode->previous = NULL;
        } else {
            ListNode *temp = node;
            node = node->next;
            while(node) {
                if (strcmp(node->name, name) == 0) {
                    temp->next = addNode;
                    addNode->previous = temp;
                    addNode->next = node;
                    node->previous = addNode;
                    return addNode;
                }
                temp = node;
                node = node->next;
            }
            temp->next = addNode;
            addNode->previous = temp;
        }
    } else {
        hashTable->table[index] = addNode;
        addNode->previous = NULL;
    }
    return addNode;
}

ListNode *hash_table_get(HashTable *hashTable, char *name) {
    int index = hash_function_pjw(name) % TABLE_SIZE;
    struct ListNode *node = hashTable->table[index];
    if (node == NULL) {
        return NULL;
    }
    if (strcmp(node->name, name) == 0) {
        return node;
    } else {
        node = node->next;
        while(node) {
            if (strcmp(node->name, name) == 0) {
                return node;
            }
            node = node->next;
        }
        return NULL;
    }
}

void hash_table_remove(HashTable *hashTable, ListNode *node) {
    ListNode *previous = node->previous;
    ListNode *next = node->next;
    if (previous) {
        previous->next = next;
        if (next) {
            node->previous = previous;
        }
    } else {
        int index = hash_function_pjw(node->name) % TABLE_SIZE;
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
//     hashTable->table[9001] = new_list_node("test", "21312");
//     ListNode *node1 = hash_table_put(hashTable, "variable", "aaa");
//     ListNode *node2 = hash_table_put(hashTable, "variable", "bbb");
//     ListNode *node3 = hash_table_put(hashTable, "variable", "bbc");
//     ListNode *node = hash_table_get(hashTable, "variable");
//     hash_table_remove(hashTable, hashTable->table[9001]);
//     return 0;
// }