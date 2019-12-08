#include <stdlib.h>
#include <stdio.h>

int *var_num;
int *temp_num;
int *label_num;
struct NumberNode *var_num_head;
struct NumberNode *var_num_tail;
struct NumberNode *temp_num_head;
struct NumberNode *temp_num_tail;
struct NumberNode *label_num_head;
struct NumberNode *label_num_tail;

typedef struct NumberNode {
    struct NumberNode *next;
    struct NumberNode *previsous;
    int *number;
} NumberNode;

NumberNode *new_number_node(int num) {
    NumberNode *number_node = (NumberNode *)malloc(sizeof(NumberNode));
    number_node->next = NULL;
    number_node->previsous = NULL;
    number_node->number = (int *)malloc(sizeof(int));
    *number_node->number = num;
    return number_node;
}

void ini_IR() {
    var_num = (int *)malloc(sizeof(int));
    temp_num = (int *)malloc(sizeof(int));
    label_num = (int *)malloc(sizeof(int));
    *var_num = 1;
    *temp_num = 1;
    *label_num = 1;
    var_num_head = NULL;
    var_num_tail = NULL;
    temp_num_head = NULL;
    temp_num_tail = NULL;
    label_num_head = NULL;
    label_num_tail = NULL;
}

int *new_num(int *num, NumberNode **head, NumberNode **tail) {
    NumberNode *node;
    node = new_number_node(*num);
    if (*num == 1) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        node->previsous = *tail;
        *tail = node;
    }
    *num += 1;
    return node->number;
}

int *new_var_num() {
    return new_num(var_num, &var_num_head, &var_num_tail);
}

int *new_temp_num() {
    return new_num(temp_num, &temp_num_head, &temp_num_tail);
}

int *new_label_num() {
    return new_num(label_num, &label_num_head, &label_num_tail);
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

void rearrange_var_num() {
    rearrange_num(var_num_head, var_num);
}

void rearrange_temp_num() {
    rearrange_num(temp_num_head, temp_num);
}

void rearrange_label_num() {
    rearrange_num(label_num_head, label_num);
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
            *tail = node->previsous;
        }
        if (*head == node) {
            *head = node->next;
        }
        if (node->previsous) {
            node->previsous->next = node->next;
            if (node->next)
                node->next->previsous = node->previsous;
        } else {
            if (node->next)
                node->next->previsous = NULL;
        }
    }
}

void delete_var_num(int number) {
    delete_num(&var_num_head, &var_num_tail, number);
}

void delete_temp_num(int number) {
    delete_num(&temp_num_head, &temp_num_tail, number);
}

void delete_label_num(int number) {
    delete_num(&label_num_head, &label_num_tail, number);
}

// int main() {
//     ini_IR();
//     int *one = new_label_num();
//     int *two = new_label_num();
//     int *three = new_label_num();
//     int *four = new_label_num();
//     delete_label_num(2);
//     printf("%d, %d, %d \n", *label_num_head->number, *label_num_head->next->number, *label_num_head->next->next->number);
//     rearrange_label_num();
//     printf("%d, %d, %d \n", *label_num_head->number, *label_num_head->next->number, *label_num_head->next->next->number);
//     puts("END");
//     return 0;
// }