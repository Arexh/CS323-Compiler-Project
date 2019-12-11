#include "IRInstruct.c"

struct IRBlock *blockStart;
struct IRBlock *blockEnd;
struct ArrayList *blocksArrayList;

typedef struct IRBlock {
    int *labelNum;
    int instructNum;
    int disable;
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
    block->disable = 0;
}

void init_IR_block() {
    IRBlock *block = new_IR_block();
    block->labelNum = new_label_num();
    blockStart = block;
    blockEnd = block;
    blocksArrayList = new_array_list();
    append_to_array_list(blocksArrayList, block);
}

IRBlock *append_new_block() {
    IRBlock *block = new_IR_block();
    block->labelNum = new_label_num();
    blockEnd->next = block;
    block->previous = blockEnd;
    blockEnd = block;
    append_to_array_list(blocksArrayList, block);
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
            if (block->jumpNext == NULL || block->jumpNext->labelNum == NULL)
                sprintf(instructs[0], "%s(NULL)", temp);
            else
                sprintf(instructs[0], "%s%d", temp, *block->jumpNext->labelNum);
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

void remove_empty_blocks() {
    int i;
    ArrayList *emptyBlocks = new_array_list();
    for (i = 0; i < blocksArrayList->memberNum; i++) {
        IRBlock *block = blocksArrayList->arr[i];
        if (block->disable)
            continue;
        if (block->instructNum == 0 && (block->next || *block->next->labelNum == *block->labelNum)) {
            append_to_array_list(emptyBlocks, block);
        } else {
            if (emptyBlocks->memberNum) {
                int j;
                for (j = 0; j < emptyBlocks->memberNum; j++) {
                    IRBlock *emptyBlock = emptyBlocks->arr[j];
                    *emptyBlock->labelNum = -1; 
                    emptyBlock->labelNum = block->labelNum;
                    emptyBlock->disable = 1;
                }
            }
            emptyBlocks->memberNum = 0;
        }
    }
}

void check_label_reference() {
    int i;
    ArrayList *arrayList = blocksArrayList;
    for (i = 0; i < arrayList->memberNum; i++) {
        IRBlock *block = arrayList->arr[i];
        if (block->next && *block->next->labelNum != *block->labelNum + 1) {
            NumberNode *node = labelNumArrayList->arr[*block->next->labelNum - 1];
            node->reference++;
        }
        if (block->jumpNext) {
            NumberNode *node = labelNumArrayList->arr[*block->jumpNext->labelNum - 1];
            node->reference++;
        }
    }
    for (i = 0; i < labelNumArrayList->memberNum; i++) {
        NumberNode *node = labelNumArrayList->arr[i];
        if (node->reference == 0) {
            *node->number = -1;
        }
    }
}

void printf_block(IRBlock *block) {
    if (block->disable)
        return;
    if (*block->labelNum != -1)
        printf("LABEL label%d :\n", *block->labelNum);
    if (block->instructNum) {
        char **arr = get_block_string(block);
        int i;
        for (i = 0; i < block->instructNum; i++) {
            printf("%s\n", arr[i]);
        }
    }
    if (block->next && *block->next->labelNum != -1 && *block->next->labelNum != *block->labelNum + 1 &&
    *block->next->labelNum != *block->labelNum)
        printf("GOTO label%d\n", *block->next->labelNum);
}

void printf_all_blocks() {
    check_label_reference();
    remove_empty_blocks();
    int i;
    for (i = 0; i < blocksArrayList->memberNum; i++) {
        printf_block((IRBlock *)blocksArrayList->arr[i]);
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


void back_patching_true_list(ArrayList *arrayList, IRBlock *block) {
    if (arrayList == NULL)
        return;
    int i;
    for (i = 0; i < arrayList->memberNum; i++) {
        IRBlock *item = arrayList->arr[i];
        item->next = block;
        append_jump_previous(block, item);
    }
}

void back_patching_false_list(ArrayList *arrayList, IRBlock *block) {
    if (arrayList == NULL)
        return;
    int i;
    for (i = 0; i < arrayList->memberNum; i++) {
        IRBlock *item = arrayList->arr[i];
        item->jumpNext = block;
        append_jump_previous(block, item);
    }
}

ArrayList *merge_list(ArrayList *listOne, ArrayList *listTwo) {
    if (listOne == NULL)
        return listTwo;
    if (listTwo == NULL)
        return listOne;
    int i;
    for (i = 0; i < listTwo->memberNum; i++) {
        append_to_array_list(listOne, listTwo->arr[i]);
    }
    free_array_list(listTwo);
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