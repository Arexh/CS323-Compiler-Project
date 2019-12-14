struct ExpRecord **varRecords;
struct ExpRecord **tempRecords;
struct ExpRecordNode *recordList;
int varNum;
int tempNum;

enum ExpressionType
{
    _NOTHING = 0, _ONE_CON, _ONE_VAR, _MINUS_ONE_CON, _MINUS_ONE_VAR, _CON_ADD_VAR, _CON_SUB_VAR, _CON_MUL_VAR, _CON_DIV_VAR, 
    _VAR_ADD_CON, _VAR_SUB_CON, _VAR_MUL_CON, _VAR_DIV_CON, _VAR_ADD_VAR, _VAR_SUB_VAR, _VAR_MUL_VAR, _VAR_DIV_VAR
};

typedef struct ExpRecord {
    int left;
    int right;
    enum ExpressionType type;
} ExpRecord;

typedef struct ExpRecordNode {
    int result;
    int left;
    int right;
    enum ExpressionType type;
    struct ExpRecordNode *next;
    struct ExpRecordNode *previous;
} ExpRecordNode;

ExpRecord *new_exp_record() {
    ExpRecord *newRecord = (ExpRecord *)malloc(sizeof(ExpRecord));
    newRecord->left = 0;
    newRecord->right = 0;
    newRecord->type = _NOTHING;
    return newRecord;
}

ExpRecordNode *new_exp_record_node() {
    ExpRecordNode *node = (ExpRecordNode *)malloc(sizeof(ExpRecordNode));
    node->result = 0;
    node->left = 0;
    node->right = 0;
    node->type = _NOTHING;
    return node;
}

void append_exp_to_list(ExpRecordNode *node) {
    if (recordList) {
        recordList->previous = node;
        node->next = recordList;
        recordList = node;
    } else {
        recordList = node;
    }
}

ExpRecordNode *find_available_exp(ExpRecord *record) {
    if (recordList == NULL) {
        return NULL;
    }
    ExpRecordNode *node = recordList;
    while(node) {
        if (record->left == node->left && record->right == node->right && record->type == node->type) {
            return node;
        } else if (record->left == node->right && record->right == node->left) {
            enum ExpressionType typeOne = record->type;
            enum ExpressionType typeTwo = node->type;
            if ((typeOne == _CON_ADD_VAR && typeTwo == _VAR_ADD_CON) 
             || (typeTwo == _CON_ADD_VAR && typeOne == _VAR_ADD_CON)) {
                return node;
            } else if ((typeOne == _CON_MUL_VAR && typeTwo == _VAR_MUL_CON) 
                    || (typeTwo == _CON_MUL_VAR && typeOne == _VAR_MUL_CON)) {
                return node;
            }
        }
        node = node->next;
    }
    return NULL;
}

void remove_exp(int num) {
    if (recordList == NULL) {
        return;
    }
    ExpRecordNode *node = recordList;
    while(node) {
        if (num == node->result) {
            if (node->previous) {
                node->previous->next = node->next;
                if (node->next)
                    node->next->previous = node->previous;
            } else {
                recordList = node->next;
                if (node->next)
                    node->next->previous = NULL;
            }
            free(node);
            break;
        }
        node = node->next;
    }
}

void new_block_container() {
    varNum = varNumArrayList->memberNum;
    tempNum = tempNumArrayList->memberNum;
    varRecords = (ExpRecord **)malloc(sizeof(ExpRecord *) * varNum);
    tempRecords = (ExpRecord **)malloc(sizeof(ExpRecord *) * tempNum);
    memset(varRecords, 0, varNum * sizeof(void *));
    memset(tempRecords, 0, tempNum * sizeof(void *));
}

void free_exp_record(ExpRecord *record) {
    record->left = 0;
    record->right = 0;
    record->type = 0;
    free(record);
}

void clear_block_container() {
    int i;
    for (i = 0; i < varNum; i++) {
        if (varRecords[i] != NULL) {
            free_exp_record(varRecords[i]);
        }
    }
    for (i = 0; i < tempNum; i++) {
        if (tempRecords[i] != NULL) {
            free_exp_record(tempRecords[i]);
        }
    }
}

void free_block_container() {
    varNum = 0;
    tempNum = 0;
    free(varRecords);
    free(tempRecords);
}

ExpRecord *put_record(int num, int left, enum ArgType leftType, int right, enum ArgType rightType, enum InstructType type) {
    ExpRecord *record = new_exp_record();
    if (type == _ASSIGN) {
        if (leftType == _CONSTANT) {
            record->type = _ONE_CON;
        } else {
            record->type = _ONE_VAR;
        }
        record->left = left;
    } else if (type == _MINUS) {
        if (leftType == _CONSTANT) {
            record->type = _MINUS_ONE_CON;
        } else {
            record->type = _MINUS_ONE_VAR;
        }
        record->left = left;
    } else if (leftType == _CONSTANT && rightType == _CONSTANT) {
        int value;
        switch(type) {
            case _PLUS:
                value = left + right;
                break;
            case _MULTIPLY:
                value = left * right;
                break;
            case _SUBSTRACT:
                value = left - right;
                break;
            case _DIVIDE:
                value = left / right;
                break;
        }
        record->type = _ASSIGN;
        record->left = value;
    } else if (leftType == _CONSTANT) {
        switch(type) {
            case _PLUS:
                record->type = _CON_ADD_VAR;
                break;
            case _MULTIPLY:
                record->type = _CON_MUL_VAR;
                break;
            case _SUBSTRACT:
                record->type = _CON_SUB_VAR;
                break;
            case _DIVIDE:
                record->type = _CON_DIV_VAR;
                break;
        }
        record->left = left;
        record->right = right;
    } else if (rightType == _CONSTANT) {
        switch(type) {
            case _PLUS:
                record->type = _VAR_ADD_CON;
                break;
            case _MULTIPLY:
                record->type = _VAR_MUL_CON;
                break;
            case _SUBSTRACT:
                record->type = _VAR_SUB_CON;
                break;
            case _DIVIDE:
                record->type = _VAR_DIV_CON;
                break;
        }
        record->left = left;
        record->right = right;
    } else {
        switch(type) {
            case _PLUS:
                record->type = _VAR_ADD_VAR;
                break;
            case _MULTIPLY:
                record->type = _VAR_MUL_VAR;
                break;
            case _SUBSTRACT:
                record->type = _VAR_SUB_VAR;
                break;
            case _DIVIDE:
                record->type = _VAR_DIV_VAR;
                break;
        }
        record->left = left;
        record->right = right;
    }
    if (num > 0) {
        ExpRecord *temp = varRecords[num - 1];
        if (temp)
            free(temp);
        varRecords[num - 1] = record;
    } else {
        ExpRecord *temp = tempRecords[-num - 1];
        if (temp)
            free(temp);
        tempRecords[-num - 1] = record;
    }
    return record;
}

ExpRecord *get_exp_record(int num) {
    if (num > 0)
        return varRecords[num - 1];
    else
        return tempRecords[-num - 1];
}

ExpRecord *update_record_recursive(int num) {
    ExpRecord *record = get_exp_record(num);
    if (record == NULL)
        return NULL;
    switch(record->type) {
        case _ONE_VAR:
            {
                ExpRecord *newRecord = update_record_recursive(record->left);
                if (newRecord) {
                    record->left = newRecord->left;
                    record->right = newRecord->right;
                    record->type = newRecord->type;
                }
                return record;
            }
        case _MINUS_ONE_VAR:
            {
                ExpRecord *newRecord = update_record_recursive(record->left);
                if (newRecord) {
                    if (newRecord->type == _ONE_VAR) {
                        record->left = newRecord->left;
                        record->type = _MINUS_ONE_VAR;
                    } else if (newRecord->type == _ONE_CON) {
                        record->left = newRecord->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (newRecord->type == _MINUS_ONE_CON) {
                        record->left = newRecord->left;
                        record->type = _ONE_CON;
                    } else if (newRecord->type == _MINUS_ONE_VAR) {
                        record->left = newRecord->left;
                        record->type = _ONE_VAR;
                    } else if (newRecord->type == _VAR_SUB_CON) {
                        record->left = newRecord->left;
                        record->right = newRecord->right;
                        record->type = _CON_SUB_VAR;
                    } else if (newRecord->type == _CON_SUB_VAR) {
                        record->left = newRecord->left;
                        record->right = newRecord->right;
                        record->type = _VAR_SUB_CON;
                    }
                }
                return record;
            }
        case _VAR_ADD_CON:
            {
                ExpRecord *left = update_record_recursive(record->left);
                if (left) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left + record->right;
                        record->type = _ONE_CON;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_ADD_CON;
                    } else if (left->type == _MINUS_ONE_CON) {
                        record->left = record->right - left->left;
                        record->type = _ONE_CON;
                    } else if (left->type == _MINUS_ONE_VAR) {
                        record->left = record->right;
                        record->right = left->left;
                        record->type = _CON_SUB_VAR;
                    } else if (left->type == _CON_ADD_VAR) {
                        record->right = left->left + record->right;
                        record->left = left->right;
                        record->type = _VAR_ADD_CON;
                    } else if (left->type == _CON_SUB_VAR) {
                        record->left = left->left + record->right;
                        record->right = left->right;
                        record->type = _CON_SUB_VAR;
                    } else if (left->type == _VAR_ADD_CON) {
                        record->left = left->left;
                        record->right = record->right + left->right;
                        record->type = _VAR_ADD_CON;
                    } else if (left->type == _VAR_SUB_CON) {
                        record->left = left->left;
                        int cal = record->right - left->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->right = 0;
                            record->type = _ONE_VAR;
                        }
                    }
                }
                return record;
            }
        case _VAR_MUL_CON:
            {
                ExpRecord *left = update_record_recursive(record->left);
                if (left) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left * record->right;
                        record->type = _ONE_CON;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_MUL_CON;
                    } else if (left->type == _MINUS_ONE_CON) {
                        record->left = -left->left * record->right;
                        record->type = _MINUS_ONE_CON;
                    } else if (left->type == _CON_MUL_VAR) {
                        record->left = left->left * record->right;
                        record->right = left->right;
                        record->type = _CON_MUL_VAR;
                    } else if (left->type == _VAR_MUL_CON) {
                        record->left = left->left;
                        record->right = left->right * record->right;  
                        record->type = _VAR_MUL_CON;
                    }
                }
                return record;
            }
        case _VAR_SUB_CON:
            {
                ExpRecord *left = update_record_recursive(record->left);
                if (left) {
                    if (left->type == _ONE_CON) {
                        int cal = left->left - record->right;
                        if (cal >= 0) {
                            record->left = cal;
                            record->type = _ONE_CON;
                        } else if (cal < 0) {
                            record->left = -cal;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_SUB_CON;
                    } else if (left->type == _MINUS_ONE_CON) {
                        record->left = left->left + record->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (left->type == _CON_ADD_VAR) {
                        record->left = left->right;
                        int cal = left->left - record->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->right = 0;
                            record->type = _ONE_VAR;
                        }
                    } else if (left->type == _CON_SUB_VAR) {
                        int cal = left->left - record->right;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = left->right;
                            record->type = _CON_SUB_VAR;
                        } else if (cal == 0) {
                            record->left = left->right;
                            record->type = _MINUS_ONE_VAR;
                        }
                    } else if (left->type == _VAR_ADD_CON) {
                        record->left = left->left;
                        int cal = left->right - record->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->right = 0;
                            record->type = _ONE_VAR;
                        }
                    } else if (left->type == _VAR_SUB_CON) {
                        record->left = left->left;
                        record->right = left->right + record->right;
                        record->type = _VAR_SUB_CON;
                    }
                }
                return record;
            }
        case _VAR_DIV_CON:
            {
                ExpRecord *left = update_record_recursive(record->left);
                if (left) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left / record->left;
                        record->type = _ONE_CON;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_DIV_CON;
                    } else if (left->type == _MINUS_ONE_CON) {
                        record->left = left->left / record->left;
                        record->type = _MINUS_ONE_CON;
                    }
                }
                return record;
            }
        case _VAR_ADD_VAR:
            {
                ExpRecord *left = update_record_recursive(record->left);
                ExpRecord *right = update_record_recursive(record->right);
                if (left == NULL && right == NULL) {
                    return record;
                } else if (left == NULL && right) {
                    if (right->type == _ONE_CON) {
                        record->right = right->left;
                        record->type = _VAR_ADD_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->right = right->left;
                        record->type = _VAR_ADD_VAR;
                    } else if (right->type == _CON_SUB_VAR) {
                        if (record->left == right->right) {
                            record->left = right->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (record->left == right->right) {
                            record->left = right->left;
                            record->type = _ONE_VAR;
                        }
                    }
                    return record;
                } else if (left && right == NULL) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left;
                        record->type = _CON_ADD_VAR;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_ADD_VAR;
                    } else if (left->type == _CON_SUB_VAR) {
                        if (left->right == record->right) {
                            record->left = left->left;
                            record->type = _ONE_CON;
                        }
                    } else if (left->type == _VAR_SUB_VAR) {
                        if (left->right == record->right) {
                            record->left = left->left;
                            record->type = _ONE_VAR;
                        }
                    }
                    return record;
                }
                if (left->type == _ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left + right->left;
                        record->type = _ONE_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _VAR_ADD_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        int cal = left->left - right->left;
                        record->type = _ONE_CON;
                        if (cal >= 0) {
                            record->left = cal;
                        } else {
                            record->left = -cal;
                        }
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _CON_ADD_VAR) {
                        record->left = left->left + right->left;
                        record->right = right->right;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _CON_SUB_VAR) {
                        record->left = left->left + right->left;
                        record->right = right->right;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _VAR_ADD_CON) {
                        record->left = left->left + right->right;
                        record->right = right->left;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _VAR_SUB_CON) {
                        record->left = right->left;
                        int cal = left->left - right->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type= _VAR_SUB_CON;
                        } else {
                            record->right = 0;
                            record->type = _ONE_VAR;
                        }
                    }
                } else if (left->type == _ONE_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_ADD_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (right->type == _CON_SUB_VAR) {
                        if (right->right == left->left) {
                            record->left = right->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (right->right == left->left) {
                            record->left = right->left;
                            record->type = _ONE_VAR;
                        }
                    }
                } else if (left->type == _MINUS_ONE_CON) {
                    if (right->type == _ONE_CON) {
                        int cal = right->left - left->left;
                        record->type = _ONE_CON;
                        if (cal >= 0) {
                            record->left = cal;
                        } else {
                            record->left = -cal;
                        }
                    } else if (right->type == _ONE_VAR) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left + right->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _CON_ADD_VAR) {
                        int cal = right->left - left->left;
                        record->left = right->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        int cal = right->left - left->left;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = right->right;
                            record->type = _CON_SUB_VAR;
                        } else if (cal == 0) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_VAR;
                        } 
                    } else if (right->type == _VAR_ADD_CON) {
                        int cal = right->right - left->left;
                        record->left = right->left;
                        if (cal > 0) {
                            record->right = cal;
                            right->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            right->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        record->left = right->left;
                        record->right = left->left + right->right;
                        record->type = _VAR_SUB_VAR;
                    }
                } else if (left->type == _MINUS_ONE_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _ONE_VAR) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (right->type == _VAR_ADD_CON) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_VAR;
                        } else if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    }
                } else if (left->type == _CON_ADD_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left + right->left;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        int cal = left->left - right->left;
                        record->left = right->left;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        int cal = left->left - right->right;
                        if (cal == 0) {
                            record->left = left->right;
                            record->right = right->left;
                            record->type = _VAR_ADD_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (right->right == left->right) {
                            record->left = left->left;
                            record->right = right->left;
                            record->type = _VAR_ADD_VAR;
                        }
                    }
                } else if (left->type == _CON_SUB_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left + right->left;
                        record->right = left->right;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _ONE_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _MINUS_ONE_CON) {
                        int cal = left->left - right->left;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = left->right;
                            record->type = _CON_SUB_VAR;
                        } else if (cal == 0) {
                            record->left = left->right;
                            record->type = _MINUS_ONE_VAR;
                        }
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->right == right->right) {
                            record->left = left->left + right->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        if (left->right == right->left) {
                            record->left = left->left + right->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->left == right->right && left->right != right->left) {
                            record->left = right->left;
                            record->right = left->right;
                            record->type = _VAR_SUB_VAR;
                        } else if (left->left == right->right && left->right == right->left) {
                            record->left = 0;
                            record->type = _ONE_CON;
                        } else if (left->left != right->right && left->right == right->left) {
                            int cal = left->left - right->right;
                            if (cal >= 0) {
                                record->left = cal;
                                record->type = _ONE_CON;
                            } else {
                                record->left = -cal;
                                record->type = _MINUS_ONE_CON;
                            }
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (left->right == right->left) {
                            record->left = right->right;
                            record->right = left->left;
                            record->type = _VAR_ADD_CON;
                        } else if (left->right == right->right) {
                            record->left = right->left;
                            record->right = left->left;
                            record->type = _VAR_ADD_CON;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _CON_SUB_VAR;
                        }
                    }
                } else if (left->type == _VAR_ADD_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left;
                        record->right = left->right + right->left;
                        record->type = _VAR_ADD_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        int cal = left->right - right->left;
                        record->left = left->left;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        }
                    } else if (right->type == _MINUS_ONE_VAR) {
                        if (left->left == right->left) {
                            record->left = left->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = left->right + right->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->right == right->right) {
                            record->left = left->left;
                            record->right = right->left;
                            record->type = _VAR_ADD_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = right->left;
                            record->right = left->right;
                            record->type = _VAR_ADD_CON;
                        }
                    }
                } else if (left->type == _VAR_SUB_CON) {
                    if (right->type == _ONE_CON) {
                        int cal = right->left - left->right;
                        record->left = left->left;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left;
                        record->right = left->right + right->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        if (left->left == right->left) {
                            record->left = left->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _VAR_ADD_VAR;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->right == right->left && left->left != right->right) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _VAR_SUB_VAR;
                        } else if (left->right == right->left && left->left == right->right) {
                            record->left = 0;
                            record->type = _ONE_CON;
                        } else if (left->right != right->left && left->left == right->right) {
                            int cal = right->left - left->right;
                            if (cal >= 0) {
                                record->left = cal;
                                record->type = _ONE_CON;
                            } else {
                                record->left = -cal;
                                record->type = _MINUS_ONE_CON;
                            }
                        }
                    } else if (left->type == _VAR_ADD_VAR) {
                        if (right->type == _MINUS_ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->type = _ONE_VAR;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->type = _ONE_VAR;
                            }
                        } else if (right->type == _CON_SUB_VAR) {
                            if (left->left == right->right) {
                                record->left = left->right;
                                record->right = right->left;
                                record->type = _VAR_ADD_CON;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_CON;
                            }
                        } else if (right->type == _VAR_SUB_VAR) {
                            if (left->left == right->right) {
                                record->left = left->right;
                                record->right = right->left;
                                record->type = _VAR_ADD_VAR;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_VAR;
                            }
                        }
                    } else if (left->type == _VAR_SUB_VAR) {
                        if (right->type == _ONE_VAR) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->type = _ONE_VAR;
                            }
                        } else if (right->type == _MINUS_ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->type = _MINUS_ONE_VAR;
                            }
                        } else if (right->type == _CON_ADD_VAR) {
                            if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_CON;
                            }
                        } else if (right->type == _CON_SUB_VAR) {
                            if (left->left == right->right) {
                                record->left = right->left;
                                record->right = left->right;
                                record->type = _CON_SUB_VAR;
                            }
                        } else if (right->type == _VAR_ADD_CON) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_ADD_CON;
                            }
                        } else if (right->type == _VAR_SUB_CON) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_SUB_CON;
                            }
                        } else if (right->type == _VAR_ADD_VAR) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_ADD_VAR;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_VAR;
                            }
                        } else if (right->type == _VAR_SUB_VAR) {
                            if (left->left == right->right && left->right == right->left) {
                                record->left = 0;
                                record->type = _ONE_CON;
                            } else if (left->left == right->right && left->right != right->left) {
                                record->left = right->left;
                                record->right = left->right;
                                record->type = _VAR_SUB_VAR;
                            } else if (left->left != right->right && left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_SUB_VAR;
                            }
                        }
                    }
                }
                return record;
            }
        case _VAR_MUL_VAR:
            {
                ExpRecord *left = update_record_recursive(record->left);
                ExpRecord *right = update_record_recursive(record->right);
                if (left == NULL && right == NULL) {
                    return record;
                } else if (left == NULL && right) {
                    if (right->type == _ONE_CON) {
                        record->right = right->left;
                        record->type = _VAR_MUL_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->right = right->left;
                        record->type = _VAR_MUL_VAR;
                    }
                    return record;
                } else if (left && right == NULL) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left;
                        record->type = _CON_MUL_VAR;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_MUL_VAR;
                    }
                    return record;
                }
                if (left->type == _ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left * right->left;
                        record->type = _ONE_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _CON_MUL_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left * right->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _CON_MUL_VAR) {
                        record->left = left->left * right->left;
                        record->right = right->right;
                        record->type = _CON_MUL_VAR;
                    }
                } else if (left->type == _ONE_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_MUL_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_MUL_VAR;
                    }
                } else if (left->type == _MINUS_ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left * right->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left * right->left;
                        record->type = _ONE_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->right;
                        record->type = _CON_MUL_VAR;
                    }
                } else if (left->type == _MINUS_ONE_VAR) {
                    if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_MUL_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_MUL_VAR;
                    }
                } else if (left->type == _CON_MUL_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left * right->left;
                        record->right = left->right;
                        record->type = _CON_MUL_VAR;
                    }
                } else if (left->type == _VAR_MUL_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left;
                        record->right = left->right * right->left;
                        record->type = _VAR_MUL_CON;
                    }
                }
                return record;
            }
        case _VAR_SUB_VAR:
            {
                ExpRecord *left = update_record_recursive(record->left);
                ExpRecord *right = update_record_recursive(record->right);
                if (left == NULL && right == NULL) {
                    return record;
                } else if (left == NULL && right) {
                    if (right->type == _ONE_CON) {
                        record->right = right->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->right = right->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->right = right->left;
                        record->type = _VAR_ADD_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->right = right->left;
                        record->type = _VAR_ADD_VAR;
                    } else if (right->type == _CON_ADD_VAR) {
                        if (record->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        if (record->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (record->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (record->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_VAR;
                        } else if (record->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (record->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_VAR;
                        }
                    }
                    return record;
                } else if (left && right == NULL) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left;
                        record->type = _CON_SUB_VAR;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (left->type == _CON_ADD_VAR) {
                        if (left->right == record->right) {
                            record->left = left->left;
                            record->type = _ONE_CON;
                        }
                    } else if (left->type == _VAR_ADD_CON) {
                        if (left->left == record->right) {
                            record->left = left->right;
                            record->type = _ONE_CON;
                        }
                    } else if (left->type == _VAR_SUB_CON) {
                        if (left->left == record->right) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (left->type == _VAR_ADD_VAR) {
                        if (left->left == record->right) {
                            record->left = left->right;
                            record->type = _ONE_VAR;
                        } else if (left->right == record->right) {
                            record->left = left->left;
                            record->type = _ONE_VAR;
                        }
                    } else if (left->type == _VAR_SUB_VAR) {
                        if (left->left == record->right) {
                            record->left = left->right;
                            record->type = _MINUS_ONE_VAR;
                        }
                    }
                    return record;
                }
                if (left->type == _ONE_CON) {
                    if (right->type == _ONE_CON) {
                        puts("HERE");
                        printf("LEFT: %d, RIGHT: %d\n", left->left, right->left);
                        int cal = left->left - right->left;
                        if (cal >= 0) {
                            record->left = cal;
                            record->type = _ONE_CON;
                        } else {
                            record->left = -cal;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left + right->left;
                        record->type = _ONE_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _CON_ADD_VAR) {
                        int cal = left->left - right->left;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = right->right;
                            record->type = _CON_SUB_VAR;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        int cal = left->left - right->left;
                        record->left = right->right;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        int cal = left->left - right->right;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = right->left;
                            record->type = _CON_SUB_VAR;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        record->left = left->left + right->right;
                        record->right = right->left;
                        record->type = _CON_SUB_VAR;
                    }
                } else if (left->type == _ONE_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left;
                        record->right = right->right;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_ADD_CON;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _VAR_ADD_VAR;
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_VAR;
                        } else if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_VAR;
                        }
                    }
                } else if (left->type == _MINUS_ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left + right->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        int cal = right->left - left->left;
                        if (cal >= 0) {
                            record->left = cal;
                            record->type = _ONE_CON;
                        } else if (cal < 0) {
                            record->left = -cal;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _CON_SUB_VAR) {
                        record->left = right->right;
                        record->right = left->left + right->left;
                        record->type = _VAR_SUB_CON;
                    } else if (right->type == _VAR_SUB_CON) {
                        if (right->right == left->left) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_VAR;
                        }
                    }
                } else if (left->type == _MINUS_ONE_VAR) {
                    if (right->type = _MINUS_ONE_CON) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        record->left = right->left;
                        record->right = left->left;
                        record->type = _VAR_SUB_VAR;
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_CON;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _MINUS_ONE_VAR;
                        }
                    }
                } else if (left->type == _CON_ADD_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->right;
                        int cal = left->left - right->left;
                        if (cal > 0) {
                            record->right = cal;
                            record->type = _VAR_ADD_CON;
                        } else if (cal < 0) {
                            record->right = -cal;
                            record->type = _VAR_SUB_CON;
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _ONE_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left + right->left;
                        record->right = left->right;
                        record->type = _CON_ADD_VAR;
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->left == right->left && left->right == right->right) {
                            record->left = 0;
                            record->type = _ONE_CON;
                        } else if (left->left == right->left && left->right != right->right) {
                            record->left = left->right;
                            record->right = right->right;
                            record->type = _VAR_SUB_VAR;
                        } else if (left->left != right->left && left->right == right->right) {
                            int cal = left->left - right->left;
                            if (cal >= 0) {
                                record->left = cal;
                                record->type = _ONE_CON;
                            } else {
                                record->left = -cal;
                                record->type = _MINUS_ONE_CON;
                            }
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->left == right->left) {
                            record->left = left->right;
                            record->right = right->right;
                            record->type = _VAR_ADD_VAR;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        if (left->left == right->right && left->right == right->left) {
                            record->left = 0;
                            record->type = _ONE_CON;
                        } else if (left->left == right->right && left->right != right->left) {
                            record->left = left->right;
                            record->right = right->left;
                            record->type = _VAR_SUB_VAR;
                        } else if (left->left != right->right && left->right == right->left) {
                            int cal = left->left - right->right;
                            if (cal >= 0) {
                                record->left = cal;
                                record->type = _ONE_CON;
                            } else {
                                record->left = -cal;
                                record->type = _MINUS_ONE_CON;
                            }
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->right == right->left) {
                            record->left = left->left + right->right;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _CON_SUB_VAR;
                        } else if (left->right == right->right) {
                            record->left = left->left;
                            record->right = right->left;
                            record->type = _CON_SUB_VAR;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _CON_ADD_VAR;
                        }
                    }
                } else if (left->type == _CON_SUB_VAR) {
                    if (right->type == _ONE_CON) {
                        int cal = left->left - right->left;
                        if (cal > 0) {
                            record->left = cal;
                            record->right = left->right;
                            record->type = _CON_SUB_VAR;
                        } else if (cal == 0) {
                            record->left = left->right;
                            record->type = _MINUS_ONE_VAR;
                        }
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left + right->left;
                        record->right = right->right;
                        record->type = _CON_SUB_VAR;
                    } else if (right->type == _MINUS_ONE_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->type = _ONE_CON;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->left == right->left && left->right == right->right) {
                            record->left = 0;
                            record->type = _ONE_CON;
                        } else if (left->left == right->left && left->right != right->right) {
                            record->left = right->right;
                            record->right = left->right;
                            record->type = _VAR_SUB_VAR;
                        } else if (left->left != right->right && left->right == right->right) {
                            int cal = left->left - right->right;
                            if (cal >= 0) {
                                record->left = cal;
                                record->type = _ONE_CON;
                            } else {
                                record->left = -cal;
                                record->type = _MINUS_ONE_CON;
                            }
                        }
                    } else if (left->type == _VAR_ADD_VAR) {
                        if (right->type == _ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                            }
                        } else if (right->type == _CON_ADD_VAR) {
                            if (left->left == right->right) {
                                record->left = left->right;
                                record->right = right->left;
                                record->type = _VAR_SUB_CON;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_SUB_CON;
                            }
                        } else if (right->type == _VAR_ADD_CON) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->right = right->right;
                                record->type = _VAR_SUB_CON;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_SUB_CON;
                            }
                        } else if (right->type == _VAR_SUB_CON) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->right = right->right;
                                record->type = _VAR_ADD_CON;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_ADD_CON;
                            }
                        } else if (right->type == _VAR_ADD_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->right = right->right;
                                record->type = _VAR_SUB_VAR;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_SUB_VAR;
                            } else if (left->left == right->right) {
                                record->left = left->right;
                                record->right = right->left;
                                record->type = _VAR_SUB_VAR;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_SUB_VAR;
                            }
                        } else if (right->type == _VAR_SUB_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->right = right->right;
                                record->type = _VAR_ADD_VAR;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_ADD_VAR;
                            }
                        }
                    } else if (left->type == _VAR_SUB_VAR) {
                        if (right->type == _ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->type = _MINUS_ONE_VAR;
                            }
                        } else if (right->type == _MINUS_ONE_VAR) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->type = _ONE_VAR;
                            }
                        } else if (right->type == _CON_SUB_VAR) {
                            if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_SUB_CON;
                            }
                        } else if (right->type == _VAR_SUB_CON) {
                            if (left->left == right->left) {
                                record->left = right->right;
                                record->right = left->right;
                                record->type = _CON_SUB_VAR;
                            }
                        } else if (right->type == _VAR_SUB_VAR) {
                            if (left->left == right->left && left->right == right->right) {
                                record->left = 0;
                                record->type = _ONE_CON;
                            } else if (left->left == right->left && left->right != right->right) {
                                record->left = right->right;
                                record->right = left->right;
                                record->type = _VAR_SUB_VAR;
                            } else if (left->left != right->left && left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_SUB_VAR;
                            }
                        }
                    }
                }
                return record;
            }
        case _VAR_DIV_VAR:
            {
                ExpRecord *left = update_record_recursive(record->left);
                ExpRecord *right = update_record_recursive(record->right);
                if (left == NULL && right == NULL) {
                    return record;
                } else if (left == NULL && right) {
                    if (right->type == _ONE_CON) {
                        record->right = right->left;
                        record->type = _VAR_DIV_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->right = right->left;
                        record->type = _VAR_DIV_VAR;
                    }
                } else if (left && right == NULL) {
                    if (left->type == _ONE_CON) {
                        record->left = left->left;
                        record->type = _CON_DIV_VAR;
                    } else if (left->type == _ONE_VAR) {
                        record->left = left->left;
                        record->type = _VAR_DIV_VAR;
                    }
                }
                if (left->type == _ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left / right->left;
                        record->type = _ONE_CON;
                    } else if (right->type == _ONE_VAR) {
                        record->left = left->left;
                        record->right = right->left;
                        record->type = _CON_DIV_VAR;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left / right->left;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _CON_DIV_VAR) {
                        record->left = left->left / right->left;
                        record->right = right->right;
                        record->type = _CON_DIV_VAR;
                    }
                } else if (left->type == _ONE_VAR) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left;
                        record->right = right->left;
                    }
                } else if (left->type == _MINUS_ONE_CON) {
                    if (right->type == _ONE_CON) {
                        record->left = left->left / right->right;
                        record->type = _MINUS_ONE_CON;
                    } else if (right->type == _MINUS_ONE_CON) {
                        record->left = left->left / right->right;
                        record->type = _ONE_CON;
                    }
                }
                return record;
            }
    }
    return record;
}

void update_instruct(ExpRecord *record, IRInstruct *instruct) {
    if (record == NULL)
        return;
    instruct->argOne = (int *)malloc(sizeof(int));
    instruct->argTwo = (int *)malloc(sizeof(int));
    *instruct->argOne = record->left;
    *instruct->argTwo = record->right;
    switch(record->type) {
        case _ONE_CON:
            instruct->argOneType = _CONSTANT;
            instruct->type = _ASSIGN;
            break;
        case _ONE_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->type = _ASSIGN;
            break;
        case _MINUS_ONE_CON:
            instruct->argOneType = _CONSTANT;
            instruct->type = _MINUS;
            break;
        case _MINUS_ONE_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->type = _MINUS;
            break;
        case _CON_ADD_VAR:
            instruct->argOneType = _CONSTANT;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _PLUS;
            break;
        case _CON_SUB_VAR:
            instruct->argOneType = _CONSTANT;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _SUBSTRACT;
            break;
        case _CON_MUL_VAR:
            instruct->argOneType = _CONSTANT;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _MULTIPLY;
            break;
        case _CON_DIV_VAR:
            instruct->argOneType = _CONSTANT;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _DIVIDE;
            break;
        case _VAR_ADD_CON:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _CONSTANT;
            instruct->type = _PLUS;
            break;
        case _VAR_SUB_CON:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _CONSTANT;
            instruct->type = _SUBSTRACT;
            break;
        case _VAR_MUL_CON:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _CONSTANT;
            instruct->type = _MULTIPLY;
            break;
        case _VAR_DIV_CON:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _CONSTANT;
            instruct->type = _DIVIDE;
            break;
        case _VAR_ADD_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _PLUS;
            break;
        case _VAR_SUB_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _SUBSTRACT;
            break;
        case _VAR_MUL_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _MULTIPLY;
            break;
        case _VAR_DIV_VAR:
            instruct->argOneType = _VAR_OR_TEMP;
            instruct->argTwoType = _VAR_OR_TEMP;
            instruct->type = _DIVIDE;
            break;
    }
}

void constant_propagation_and_folding() {
    int i;
    int blocksNum = blocksArrayList->memberNum;
    new_block_container();
    for (i = 0; i < blocksNum; i++) {
        IRBlock *block = blocksArrayList->arr[i];
        int j;
        int instructNum = block->instructNum;
        IRInstruct *instruct = block->instructHead;
        printf("%d\n", instructNum);
        for (j = 1; j < instructNum; j++) {
            int argOne = 0;
            int argOneType;
            if (instruct->argOne) {
                argOne = *instruct->argOne;
                argOneType = instruct->argOneType;
                if (argOneType != _CONSTANT && argOneType != _VAR_OR_TEMP)
                    continue;
            }
            int argTwo = 0;
            int argTwoType;
            if (instruct->argTwo) {
                argTwo = *instruct->argTwo;
                argTwoType = instruct->argTwoType;
                if (argTwoType != _CONSTANT && argTwoType != _VAR_OR_TEMP)
                    continue;
            }
            int result;
            if (instruct->result)
                result = *instruct->result;
            printf("TYPE: %d\n", instruct->type);
            switch(instruct->type) {
                case _ASSIGN:
                case _MINUS:
                {   
                    put_record(result, argOne, argOneType, 0, 0, instruct->type);
                    ExpRecord *record = update_record_recursive(result);
                    remove_exp(result);
                    update_instruct(record, instruct);
                    ExpRecordNode *re = find_available_exp(record);
                    if (re && re->result < 0 && result > 0) {
                        re->result = result;
                    }
                    break;
                }
                case _PLUS:
                case _MULTIPLY:
                case _SUBSTRACT:
                case _DIVIDE:
                {
                    put_record(result, argOne, argOneType, argTwo, argTwoType, instruct->type);
                    ExpRecord *record = update_record_recursive(result);
                    switch(record->type) {
                        case _ONE_CON:
                        case _ONE_VAR:
                        case _MINUS_ONE_CON:
                        case _MINUS_ONE_VAR:
                            remove_exp(result);
                            break;
                        default:
                        {
                            ExpRecordNode *re = find_available_exp(record);
                            if (re) {
                                record->left = re->result;
                                record->type = _ONE_VAR;
                            } else {
                                remove_exp(result);
                                ExpRecordNode *node = new_exp_record_node();
                                node->left = record->left;
                                node->right = record->right;
                                node->type = record->type;
                                node->result = result;
                                append_exp_to_list(node);
                            }
                            break;
                        }
                    }
                    update_instruct(record, instruct);
                    break;
                }
                case _RETURN:
                case _WRITE:
                {
                    ExpRecord *record = update_record_recursive(argOne);
                    ExpRecordNode *re = find_available_exp(record);
                    if (re) {
                        record->left = re->result;
                        record->type = _ONE_VAR;
                    }
                    switch(record->type) {
                        case _ONE_CON:
                            instruct->argOne = (int *)malloc(sizeof(int));
                            *instruct->argOne = record->left;
                            instruct->argOneType = _CONSTANT;
                            break;
                        case _ONE_VAR:
                            instruct->argOne = (int *)malloc(sizeof(int));
                            *instruct->argOne = record->left;
                            instruct->argOneType = _VAR_OR_TEMP;
                            break;
                    }
                    break;
                }
            }
            instruct = instruct->next;
        }
        clear_block_container();
        new_block_container();
    }
    free_block_container();
}