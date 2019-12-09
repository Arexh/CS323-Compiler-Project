#include "IRInstruct.c"

typedef struct IRBlock {
    int label_num;
    int instruct_num;
    struct IRInstruct *instruct_head;
    struct IRInstruct *instruct_tail;
    struct IRBlock *next;
    struct IRBlock *previous;
    struct IRBlock *jump_next;
    struct IRBlock *jump_previous;
} IRBlock;

IRBlock *new_IR_block() {
    IRBlock *block = (IRBlock *)malloc(sizeof(IRBlock));
    block->label_num = 0;
    block->instruct_num = 0;
    block->instruct_head = NULL;
    block->instruct_tail = NULL;
    block->next = NULL;
    block->previous = NULL;
    block->jump_next = NULL;
    block->jump_previous = NULL;
}

void add_instruct(IRBlock *block, IRInstruct *instruct) {
    if (block->instruct_num == 0) {
        block->instruct_head = instruct;
        block->instruct_tail = instruct;
        block->instruct_num = 1;
    } else {
        block->instruct_tail->next = instruct;
        instruct->previous = block->instruct_tail;
        block->instruct_tail = instruct;
        block->instruct_num ++;
    }
}

char **get_block_string(IRBlock *block) {
    char **instructs = (char **)malloc(sizeof(char *) * block->instruct_num);
    IRInstruct *first = block->instruct_head;
    switch(first->type) {
        case LESSTHAN:
        case LESSEQUAL:
        case GREATERTHAN:
        case GREATEREQUAL:
        case NOTEQUAL:
        case EQUAL:
            instructs[0] = (char *)malloc(sizeof(char) * 128);
            char temp[128];
            get_IR_instruct_string(temp, first);
            sprintf(instructs[0], "%s %d", temp, block->jump_next->label_num);
            return instructs;
    }
    int index;
    for (index = 0; index < block->instruct_num; index ++) {
        instructs[index] = (char *)malloc(sizeof(char) * 128);
        get_IR_instruct_string(instructs[index], first);
        first = first->next;
    }
    return instructs;
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