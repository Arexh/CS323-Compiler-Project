struct ArrayList *varRecord;
struct ArrayList *tempRecord;

enum ExpressionType
{
    _NOTHING = 0,
    _ONE_CON,
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

typedef struct ExpRecord {
    int left;
    int right;
    enum ExpressionType type;
};

void new_block_container() {
    varRecord = new_array_list_size(varNumArrayList->memberNum);
    tempRecord = new_array_list_size(tempNumArrayList->memberNum);
    memset(varRecord->arr, 0, sizeof(varNumArrayList->memberNum) * sizeof(void *));
    memset(tempRecord->arr, 0, sizeof(tempNumArrayList->memberNum) * sizeof(void *));
}

void free_block_container() {
    
}

void put_constant(int num, int constant) {
    NumberNode *node = get_number_node(num);
    node->type = _ONE_CON;
    node->left = constant;
}

void constant_propagation() {
    int i;
    int blocksNum = blocksArrayList->memberNum;
    for (i = 0; i < blocksNum; i++) {
        IRBlock *block = blocksArrayList->arr[i];
        int j;
        int instructNum= block->instructNum;
        IRInstruct *instruct = block->instructHead;
        for (j = 1; j < instructNum; j++) {
            int argOne = *instruct->argOne;
            int argOneType = instruct->argOneType;
            switch(instruct->type) {
                case _ASSIGN:
                    if (argOneType == _CONSTANT) {
                        put_constant(*instruct->result, argOne);
                    } else {
                        NumberNode *var = get_number_node(argOne);
                        if (var->type == _ONE_CON) {
                            instruct->argOne = (int *)malloc(sizeof(int));
                            *instruct->argOne = var->left;
                            instruct->argOneType = _CONSTANT;
                        }
                    }
                    break;
            }
            instruct = instruct->next;
        }
    }
}