#include <stdlib.h>
#include <stdio.h>

struct ArrayList *varNumArrayList;
struct ArrayList *tempNumArrayList;
struct ArrayList *labelNumArrayList;

enum ExpressionType
{
    _ONE_CON = 1,
    _TWO_CON,
    _CON_ADD_VAR,
    _CON_SUB_VAR,
    _CON_MUL_VAR,
    _CON_DIV_VAR,
    _VAR_ADD_CON,
    _VAR_SUB_CON,
    _VAR_MUL_CON,
    _VAR_DIV_CON,
    _VAR_ADD_VAR,
    _VAR_SUB_VAR,
    _VAR_MUL_VAR,
    _VAR_DIV_VAR
};

typedef struct NumberNode {
    enum ExpressionType type;
    int changed;
    int left;
    int right;
    int *number;
} NumberNode;

NumberNode *new_number_node(int num) {
    NumberNode *number_node = (NumberNode *)malloc(sizeof(NumberNode));
    number_node->number = (int *)malloc(sizeof(int));
    *number_node->number = num;
    return number_node;
}

void init_number_control() {
    varNumArrayList = new_array_list();
    tempNumArrayList = new_array_list();
    labelNumArrayList = new_array_list();
}

void free_number_node(NumberNode *node) {
    free(node->number);
    free(node);
}

int *new_num(ArrayList *arrayList) {
    NumberNode *node = new_number_node(arrayList->memberNum + 1);
    append_to_array_list(arrayList, node);
    return node->number;
}

int *new_var_num() {
    return new_num(varNumArrayList);
}

int *new_temp_num() {
    int *num = new_num(tempNumArrayList);
    *num = -*num;
    return num;
}

int *new_label_num() {
    return new_num(labelNumArrayList);
}