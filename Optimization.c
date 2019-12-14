struct ExpRecord **varRecords;
struct ExpRecord **tempRecords;
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

ExpRecord *new_exp_record() {
    ExpRecord *record = (ExpRecord *)malloc(sizeof(ExpRecord));
    record->left = 0;
    record->right = 0;
    record->type = _NOTHING;
    return record;
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
        varRecords[num - 1] = record;
    } else {
        tempRecords[-num - 1] = record;
    }
    return record;
}

void put_constant(int num, int constant) {
    put_record(num, constant, _CONSTANT, 0, 0, _ASSIGN);
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
            ExpRecord *newRecord = update_record_recursive(record->left);
            if (newRecord) {
                record->left = newRecord->left;
                record->right = newRecord->right;
                record->type = newRecord->type;
                return record;
            }
            return NULL;
        case _MINUS_ONE_VAR:
            newRecord = update_record_recursive(record->left);
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
                } else {
                    return NULL;
                }
                return record;
            }
            return NULL;
        case _VAR_ADD_CON:
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
                    record->right = right->right + left->right;
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
                } else {
                    return NULL;
                }
                return record;
            }
            return NULL;
        case _VAR_MUL_CON:
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
                    record->right = left->right * right->right;  
                    record->type = _VAR_MUL_CON;
                } else {
                    return NULL;
                }
                return left;
            }
            return NULL;
        case _VAR_SUB_CON:
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
                    int cal = left->left - right->right;
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
                    int cal = left->left - right->right;
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
                } else {
                    return NULL;
                }
                return record;
            }
            return NULL;
        case _VAR_DIV_CON:
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
                } else {
                    return NULL;
                }
                return record;
            }
            return NULL:
        case _VAR_ADD_VAR:
            ExpRecord *left = update_record_recursive(record->left);
            ExpRecord *right = update_record_recursive(record->right);
            if (left && right) {
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
                    } else {
                        return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (right->right == left->left) {
                            record->left = right->left;
                            record->type = _ONE_VAR;
                        } else {
                            return NULL;
                        }
                    } else {
                        return NULL;
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
                        } else {
                            return NULL:
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
                    } else {
                        return NULL;
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
                            record->type = _ONE_CON
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_ADD_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _ONE_VAR;
                        } else if (left->left == right->right) {
                            record->left = right->left;
                            record->type = _ONE_VAR;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->left) {
                            record->left = right->right;
                            record->type = _MINUS_ONE_CON;
                        } else {
                            return NULL;
                        }
                    } else {
                        return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (right->right == left->right) {
                            record->left = left->left;
                            record->right = right->left;
                            record->type = _VAR_ADD_VAR;
                        } else {
                            return NULL;
                        }
                    } else {
                        return NULL;
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
                        } else {
                            return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->right == right->right) {
                            record->left = left->left + right->left;
                            record->type = _ONE_CON;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_ADD_CON) {
                        if (left->right == right->left) {
                            record->left = left->left + right->right;
                            record->type = _ONE_CON;
                        } else {
                            return NULL;
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
                        } else {
                            return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _CON_SUB_VAR;
                        } else {
                            return NULL;
                        }
                    } else {
                        return NULL;
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
                        } else {
                            record->type = _ONE_VAR;
                        }
                    } else if (right->type == _MINUS_ONE_VAR) {
                        if (left->left == right->left) {
                            record->left = left->right;
                            record->type = _ONE_CON;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _CON_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = left->right + right->left;
                            record->type = _ONE_CON;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_CON) {
                        if (left->right == right->right) {
                            record->left = left->left;
                            record->right = right->left;
                            record->type = _VAR_ADD_VAR;
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _VAR_SUB_VAR) {
                        if (left->left == right->right) {
                            record->left = right->left;
                            record->right = left->right;
                            record->type = _VAR_ADD_CON;
                        } else {
                            return NULL;
                        }
                    } else {
                        return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (right->type == _CON_ADD_VAR) {
                        if (left->right == right->left) {
                            record->left = left->left;
                            record->right = right->right;
                            record->type = _VAR_ADD_VAR;
                        } else {
                            return NULL;
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
                        } else {
                            return NULL;
                        }
                    } else if (left->type == VAR_ADD_VAR) {
                        if (right->type == _MINUS_ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->type = _ONE_VAR;
                            } else if (left->right == right->left) {
                                record->left = left->left;
                                record->type = _ONE_VAR;
                            } else {
                                return NULL;
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
                            } else {
                                return NULL;
                            }
                        } else if (right->type == VAR_SUB_VAR) {
                            if (left->left == right->right) {
                                record->left = left->right;
                                record->right = right->left;
                                record->type = _VAR_ADD_VAR;
                            } else if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_VAR;
                            } else {
                                return NULL;
                            }
                        } else {
                            return NULL;
                        }
                    } else if (left->type == _VAR_SUB_VAR) {
                        if (right->type == _ONE_VAR) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->type = _ONE_VAR;
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _MINUS_ONE_VAR) {
                            if (left->left == right->left) {
                                record->left = left->right;
                                record->type = _MINUS_ONE_VAR;
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _CON_ADD_VAR) {
                            if (left->right == right->right) {
                                record->left = left->left;
                                record->right = right->left;
                                record->type = _VAR_ADD_CON;
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _CON_SUB_VAR) {
                            if (left->left == right->right) {
                                record->left = right->left;
                                record->right = left->right;
                                record->type = _CON_SUB_VAR;
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _VAR_ADD_CON) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_ADD_CON;
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _VAR_SUB_CON) {
                            if (left->right == right->left) {
                                record->left = left->left;
                                record->right = right->right;
                                record->type = _VAR_SUB_CON;
                            } else {
                                return NULL;
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
                            } else {
                                return NULL;
                            }
                        } else if (right->type == _VAR_SUB_VAR) {
                            if (left->left == right->right && left->right == right->left) {
                                record->left = 0;
                                record->type = _ONE_CON;
                            } else if (left->left == right->right && left->right != right->left) {

                            }
                        }
                    }
                }
            }
            break;
        case _VAR_MUL_VAR:
            break;
        case _VAR_SUB_VAR:
            break;
        case _VAR_DIV_VAR:
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
        for (j = 1; j < instructNum; j++) {
            int argOne = 0;
            int argOneType;
            if (instruct->argOne) {
                argOne = *instruct->argOne;
                argOneType = instruct->argOneType;
            }
            int argTwo = 0;
            int argTwoType;
            if (instruct->argTwo) {
                argTwo = *instruct->argTwo;
                argTwoType = instruct->argTwoType;
            }
            switch(instruct->type) {
                case _ASSIGN:
                    if (argOneType == _CONSTANT) {
                        put_constant(*instruct->result, argOne);
                    } else {
                        ExpRecord *record = get_exp_record(argOne);
                        if (record && record->type == _ONE_CON) {
                            instruct->argOne = (int *)malloc(sizeof(int));
                            instruct->argOneType = _CONSTANT;
                            *instruct->argOne = record->left;
                            if (record->left >= 0) {
                                *instruct->argOne = record->left;
                            } else {
                                *instruct->argOne = -record->left;
                                instruct->type = _MINUS; 
                            }
                        }
                    }
                    break;
                case _MINUS:
                    if (argOneType == _CONSTANT) {
                        put_constant(*instruct->result, -argOne);
                    } else {
                        ExpRecord *record = get_exp_record(argOne);
                        if (record && record->type == _ONE_CON) {
                            instruct->argOne = (int *)malloc(sizeof(int));
                            *instruct->argOne = record->left;
                            instruct->argOneType = _CONSTANT;
                        }
                    }
                case _PLUS:
                case _MULTIPLY:
                case _SUBSTRACT:
                case _DIVIDE:
                    if (argOneType == _CONSTANT && argTwoType == _CONSTANT) {
                        ExpRecord *record = put_record(*instruct->result, argOne, argOneType, argTwo, argTwoType, instruct->type);
                        *instruct->type = _ASSIGN;
                        instruct->argTwo = NULL;
                        instruct->argTwoType = 0;
                        instruct->argOne = record->left;
                    } else if (argOneType == _CONSTANT) {
                        ExpRecord *rightRecord = get_exp_record(argTwo);
                        if (rightRecord && rightRecord->type == _ONE_CON) {
                            ExpRecord *record = put_record(*instruct->result, argOne, argOneType, rightRecord->left, _CONSTANT, instruct->type);
                            *instruct->type = _ASSIGN;
                            instruct->argTwo = NULL;
                            instruct->argTwoType = 0;
                            instruct->argOne = record->left;
                        } else if (rightRecord && rightRecord->type == _ONE_VAR) {
                            ExpRecord *newRecord = update_record_recursive(rightRecord);
                        }
                    }
                    break;

            }
            instruct = instruct->next;
        }
        clear_block_container();
    }
    free_block_container();
}