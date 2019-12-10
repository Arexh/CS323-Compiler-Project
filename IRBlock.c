#include "IRInstruct.c"

struct IRBlock *blockStart;
struct IRBlock *blockEnd;
int totalBlockNum;

typedef struct IRBlock {
    int *labelNum;
    int instructNum;
    struct IRInstruct *instructHead;
    struct IRInstruct *instructTail;
    struct IRBlock *next;
    struct IRBlock *previous;
    struct IRBlock *jumpNext;
    struct IRBlockNode *jumpPrevious;
} IRBlock;

typedef struct IRBlockNode {
    struct IRBlock **block;
    struct IRBlockNode *next;
} IRBlockNode;

IRBlockNode *new_IR_block_node() {
    IRBlockNode *node = (IRBlockNode *)malloc(sizeof(IRBlockNode));
    node->block = (IRBlock **)malloc(sizeof(IRBlock *));
    node->next = NULL;
    return node;
}

void free_block_node(IRBlockNode *node) {
    node->block = NULL;
    free(node->block);
    node->next = NULL;
    free(node);
}

IRBlock *new_IR_block() {
    IRBlock *block = (IRBlock *)malloc(sizeof(IRBlock));
    block->labelNum = NULL;
    block->instructNum = 0;
    block->instructHead = NULL;
    block->instructTail = NULL;
    block->next = NULL;
    block->previous = NULL;
    block->jumpNext = NULL;
    block->jumpPrevious = NULL;
}

void init_IR_block() {
    IRBlock *block = new_IR_block();
    block->labelNum = new_label_num();
    blockStart = block;
    blockEnd = block;
    totalBlockNum = 1;
}

IRBlock *append_new_block() {
    IRBlock *block = new_IR_block();
    block->labelNum = new_label_num();
    blockEnd->next = block;
    block->previous = blockEnd;
    blockEnd = block;
    totalBlockNum++;
    return block;
}

IRInstruct *append_new_instruct(IRBlock *block) {
    IRInstruct *instruct = new_IR_instruct();
    if (block->instructNum == 0) {
        block->instructHead = instruct;
        block->instructTail = instruct;
        block->instructNum = 1;
    } else {
        block->instructTail->next = instruct;
        instruct->previous = block->instructTail;
        block->instructTail = instruct;
        block->instructNum ++;
    }
    return instruct;
}

char **get_block_string(IRBlock *block) {
    char **instructs = (char **)malloc(sizeof(char *) * block->instructNum);
    IRInstruct *first = block->instructHead;
    switch(first->type) {
        case _LESSTHAN:
        case _LESSEQUAL:
        case _GREATERTHAN:
        case _GREATEREQUAL:
        case _NOTEQUAL:
        case _EQUAL:
            instructs[0] = (char *)malloc(sizeof(char) * 128);
            char temp[128];
            get_IR_instruct_string(temp, first);
            sprintf(instructs[0], "%s %d", temp, *block->jumpNext->labelNum);
            return instructs;
    }
    int index;
    for (index = 0; index < block->instructNum; index ++) {
        instructs[index] = (char *)malloc(sizeof(char) * 128);
        get_IR_instruct_string(instructs[index], first);
        first = first->next;
    }
    return instructs;
}

void printf_all_blocks() {
    // int check[totalBlockNum] = {0};
    // IRBlock *block = blockStart;
    // while(block) {

    // }
}

void printf_block(IRBlock *block) {
    if (block->instructNum) {
        char **arr = get_block_string(block);
        int i;
        printf("LABLE label%d :\n", *block->labelNum);
        for (i = 0; i < block->instructNum; i++) {
            printf("%s\n", arr[i]);
        }
        if (block->next)
            printf("GOTO label%d\n", *block->next->labelNum);
    }
}


void append_jump_previous(IRBlock *block, IRBlock *previous) {
    if (block->jumpPrevious) {
        IRBlockNode *temp = block->jumpPrevious;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_IR_block_node();
        temp->next->block = &previous;
    } else {
        block->jumpPrevious = new_IR_block_node();
        block->jumpPrevious->block = &previous;
    }
}


void back_patching(IRBlockNode *list, IRBlock *block) {
    if (list == NULL)
        return;
    IRBlockNode *temp = list;
    while(temp) {
        *temp->block = block;
        append_jump_previous(block, *temp->block);
        IRBlockNode *remove = temp;
        temp = temp->next;
        free_block_node(remove);
    }
}

IRBlockNode *merge_list(IRBlockNode *listOne, IRBlockNode *listTwo) {
    if (listOne == NULL)
        return listTwo;
    IRBlockNode *temp = listOne;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = listTwo;
    return listOne;
}

void append_node_to_list(IRBlockNode *list, IRBlock *block) {
    IRBlockNode *temp = list;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_IR_block_node();
    temp->next->block = &block;
}

// int main() {
//     IRBlock *block = new_IR_block();
//     IRInstruct *instruct = new_IR_instruct();
//     instruct->type = PLUS;
//     instruct->arg_two_type = CONSTANT;
//     instruct->arg_two = 21321;
//     IRInstruct *instruct_two = new_IR_instruct();
//     instruct_two->type = MINUS;
//     instruct_two->arg_two_type = CONSTANT;
//     instruct_two->arg_two = 21321;
//     IRBlock *next_block = new_IR_block();
//     block->jump_next = next_block;
//     add_instruct(block, instruct);
//     add_instruct(block, instruct_two);
//     char ** instructs = get_block_string(block);
//     int i;
//     for (i = 0; i < block->instruct_num; i ++) {
//         printf("%s\n", instructs[i]);
//     }
//     puts("END");
//     return 0;
// }