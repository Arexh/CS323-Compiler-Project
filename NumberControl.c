#include <stdlib.h>
#include <stdio.h>

int *varNum;
int *tempNum;
int *labelNum;
struct NumberNode *varNumHead;
struct NumberNode *varNumTail;
struct NumberNode *tempNumHead;
struct NumberNode *tempNumTail;
struct NumberNode *labelNumHead;
struct NumberNode *labelNumTail;

typedef struct NumberNode {
    struct NumberNode *next;
    struct NumberNode *previous;
    int *number;
} NumberNode;

NumberNode *new_number_node(int num) {
    NumberNode *number_node = (NumberNode *)malloc(sizeof(NumberNode));
    number_node->next = NULL;
    number_node->previous = NULL;
    number_node->number = (int *)malloc(sizeof(int));
    *number_node->number = num;
    return number_node;
}

void init_number_control() {
    varNum = (int *)malloc(sizeof(int));
    tempNum = (int *)malloc(sizeof(int));
    labelNum = (int *)malloc(sizeof(int));
    *varNum = 1;
    *tempNum = 1;
    *labelNum = 1;
    varNumHead = NULL;
    varNumTail = NULL;
    tempNumHead = NULL;
    tempNumTail = NULL;
    labelNumHead = NULL;
    labelNumTail = NULL;
}

void free_number_node(NumberNode *node) {
    node->next = NULL;
    node->previous = NULL;
    free(node->number);
    free(node);
}

int *new_num(int *num, NumberNode **head, NumberNode **tail) {
    NumberNode *node;
    node = new_number_node(*num);
    if (*num == 1) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        node->previous = *tail;
        *tail = node;
    }
    *num += 1;
    return node->number;
}

int *new_var_num() {
    return new_num(varNum, &varNumHead, &varNumTail);
}

int *new_temp_num() {
    return new_num(tempNum, &tempNumHead, &tempNumTail);
}

int *new_label_num() {
    return new_num(labelNum, &labelNumHead, &labelNumTail);
}

void rearrange_num(NumberNode *head, int *num) {
    int index = 1;
    NumberNode *node = head;
    while (node != NULL) {
        *node->number = index++;
        node = node->next;
    }
    *num = index;
}

void rearrange_varNum() {
    rearrange_num(varNumHead, varNum);
}

void rearrange_tempNum() {
    rearrange_num(tempNumHead, tempNum);
}

void rearrange_labelNum() {
    rearrange_num(labelNumHead, labelNum);
}

void delete_num(NumberNode **head, NumberNode **tail, int number) {
    NumberNode *node = *head;
    while(node != NULL && *node->number != number) {
        node = node->next;
    }
    if (node == NULL) {
        printf("Can not find number: %d\n", number);
    } else {
        if (*tail == node) {
            *tail = node->previous;
        }
        if (*head == node) {
            *head = node->next;
        }
        if (node->previous) {
            node->previous->next = node->next;
            if (node->next)
                node->next->previous = node->previous;
        } else {
            if (node->next)
                node->next->previous = NULL;
        }
        free_number_node(node);
    }
}

void delete_varNum(int number) {
    delete_num(&varNumHead, &varNumTail, number);
}

void delete_tempNum(int number) {
    delete_num(&tempNumHead, &tempNumTail, number);
}

void delete_labelNum(int number) {
    delete_num(&labelNumHead, &labelNumTail, number);
}


// int main() {
//     ini_IR();
//     int *one = new_labelNum();
//     int *two = new_labelNum();
//     int *three = new_labelNum();
//     int *four = new_labelNum();
//     delete_labelNum(2);
//     printf("%d, %d, %d \n", *labelNum_head->number, *labelNum_head->next->number, *labelNum_head->next->next->number);
//     rearrange_labelNum();
//     printf("%d, %d, %d \n", *labelNum_head->number, *labelNum_head->next->number, *labelNum_head->next->next->number);
//     puts("END");
//     return 0;
// }