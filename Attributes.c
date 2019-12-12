#include "ArrayList.c"
#include "ASTNode.c"
#include "NumberControl.c"
#include "HashTable.c"
#include "SymbolTable.c"
#include "Struct.c"
#include "IRBlock.c"

struct FunctionAttribute *currentFunction;
int currentScopeNumber;
int _assign;

typedef struct Parameter {
    char *type;
    int dimension;
    int *dimensions;
    TableItem *item;
    struct StructAttribute *attribute;
    struct Parameter *next;
} Parameter;

Parameter *new_parameter() {
    Parameter *para = (Parameter *)malloc(sizeof(Parameter));
    para->type = NULL;
    para->dimension = 0;
    para->attribute = NULL;
    para->dimensions = NULL;
    para->item = NULL;
    return para;
}

typedef struct FunctionAttribute {
    char *returnType;
    char *ID;
    int re;
    struct StructAttribute *attribute;
    HashTable *hashTable;
    ArrayList *parameters;
    struct FunctionAttribute *next;
} FunctionAttribute;

FunctionAttribute *new_function_attribute(char *returnType, char *ID) {
    FunctionAttribute *attribute = (FunctionAttribute *)malloc(sizeof(FunctionAttribute));
    attribute->returnType = returnType;
    attribute->ID = ID;
    attribute->hashTable = new_hash_table();
    attribute->next = NULL;
    attribute->parameters = new_array_list();
    attribute->attribute = NULL;
    attribute->re = 0;
    return attribute;
}

void append_new_parameter(FunctionAttribute *func, Parameter *new) {
    append_to_array_list(func->parameters, new);
}

TableItem *put_node(char* ID, char* type, void *attribute, int scopeNum, int dimension, int *dimensions) {
    if (currentSymbolTable) {
        return symbol_table_add_node(currentTable, currentSymbolTable, ID, type, attribute, scopeNum, dimension, dimensions);
    } else {
        return hash_table_put(currentTable, ID, type, attribute, scopeNum, dimension, dimensions);
    }
}

// 0: not initialized, 1: initialize, -1: ID already used
int scope_check(HashTable *hashTable, char *ID, char *type) {
    TableItem *item = hash_table_get(hashTable, ID);
    if (item == NULL) {
        return 0;
    }
    FunctionAttribute *attribute = item->attribute;
    while(item) {
        if (strcmp(item->ID, ID) == 0 && currentScopeNumber == item->scopeNum) {
            if (strcmp(item->type, type) == 0) {
                return 1;
            } else {
                if (strcmp(type, "struct") && strcmp(item->type, "struct")) {
                    return -1;
                }
            }
        }
        item = item->next;
    }
    return 0;
}

int struct_scope_check(HashTable *hashTable, char *ID) {
    return scope_check(hashTable, ID, "struct");
}

int function_scope_check(HashTable *hashTable, char *ID) {
    return scope_check(hashTable, ID, "function");
}

int variable_scope_check(HashTable *hashTable, char *ID, char *type) {
    return scope_check(hashTable, ID, type);
}

int function_stack_push(ASTNode *specifier, char *ID, int IDLineNo) {
    int check = function_scope_check(currentTable, ID);
    if (check == 1) {
        fprintf(out, "Error type 4 at Line %d: function is redeﬁned\n", IDLineNo);
        return 1;
    } else if (check == -1) {
        fprintf(out, "Error type 21 at Line %d: function ID is already used by a variable.\n", IDLineNo);
        return 1;
    }
    FunctionAttribute *attribute;
    if (specifier->child_count == 0) {
        // TYPE
        char *returnType = specifier->value;
        attribute = new_function_attribute(returnType, ID);
        // put function into symbol table
        put_node(ID, "function", attribute, currentScopeNumber, 0, NULL);
    } else if (specifier->child_count == 2) {
        // STRUCT ID, scope check
        char *structID = specifier->child[1]->value;
        int check = struct_scope_check(currentTable, structID);
        if (check == 0) {
            // struct is not defined, print error
            fprintf(out, "Error type 15 at Line %d: struct is used without deﬁnition\n", specifier->child[1]->row);
            return 1;
        } else if (check == 1) {
            // returnType = struct ID
            attribute = new_function_attribute("structVariable", ID);
            attribute->attribute = find_struct(currentTable, structID)->attribute;
            put_node(ID, "function", attribute, currentScopeNumber, 0, NULL);
        } else if (check == -1) {
            fprintf(out, "Error type 19 at Line %d: use variable as struct ID\n", specifier->child[1]->row);
            return 1;
        }
    } else {
        // declare strunct is not allowed, print error
        fprintf(out, "Error type 17 at Line %d: declare struct in function specifier is not allowed\n", specifier->child[0]->row);
        return 1;
    }
    if (attribute) {
        if (currentFunction) {
            attribute->next = currentFunction;
            currentFunction = attribute;
        } else {
            currentFunction = attribute;
        }
    }
    return 0;
}

void function_stack_pop() {
    currentFunction = currentFunction->next;
}

typedef struct TypeArrayAttribute {
    char *type;
    int dimension;
} TypeArrayAttribute;

TypeArrayAttribute *new_type_array_attribute(char *type, int dimension) {
    TypeArrayAttribute *attribute = (TypeArrayAttribute *)malloc(sizeof(TypeArrayAttribute));
    attribute->type = type;
    attribute->dimension = dimension;
    return attribute;
}

StructAttribute *put_struct_specifier(ASTNode *specifier) {
    // STRUCT ID LC DefList RC
    ASTNode *defList = specifier->child[3];
    StructAttribute *structAttribute;
    char *structID = specifier->child[1]->value;
    if (strcmp(defList->type, "NONE")) {
        int varNum = *((int *)specifier->child[3]->value);
        structAttribute = new_struct_attribute(varNum);
        int index = 0;
        while(strcmp(defList->type, "NONE")) {
            ASTNode *def = defList->child[0];
            char *specifier;
            char *specifierType = def->child[0]->child[0]->type;
            char *insideStructID;
            TableItem *structItem;
            if (strcmp(specifierType, "TYPE") == 0) {
                // TYPE
                specifier = def->child[0]->child[0]->value;
            } else {
                // StructSpecifier
                specifier = "struct";
                ASTNode *structSpecifier = def->child[0]->child[0];
                if (structSpecifier->child_count == 5) {
                    fprintf(out, "Error at Line %d: declare a struct inside another struct is not allowed\n", structSpecifier->row);
                    defList = defList->child[1];
                    continue;
                } else {
                    insideStructID = structSpecifier->child[1]->value;
                    if (strcmp(insideStructID, structID)) {
                        structItem = find_struct(currentTable, insideStructID);
                        if (structItem == NULL) {
                            fprintf(out, "Error at Line %d: undifined struct \"%s\"\n", structSpecifier->row, insideStructID);
                            defList = defList->child[1];
                            continue;
                        }
                    }
                }
            }
            ASTNode *decList = def->child[1];
            while(1) {
                ASTNode *dec = decList->child[0];
                if (dec->child_count == 3) {
                    fprintf(out, "Error at Line %d: assignment in struct is not allowed\n", dec->row);
                } else {
                    ASTNode *varDec = dec->child[0];
                    int dimension = 0;
                    while (varDec->child_count == 4) {
                        varDec = varDec->child[0];
                        dimension++;
                    }
                    StructVariable *var = new_struct_variable();
                    var->type = specifier;
                    var->ID = varDec->child[0]->value;
                    var->dimension = dimension;
                    if (strcmp(specifier, "struct") == 0) {
                        var->structID = insideStructID;
                        var->type = "structVariable";
                        if (strcmp(insideStructID, structID) == 0) {
                            var->attribute = structAttribute;
                        } else {
                            var->attribute = structItem->attribute;
                        }
                    }
                    structAttribute->varDec[index++] = var;
                }
                if (decList->child_count == 1) {
                    break;
                }
                decList = decList->child[2];
            }
            defList = defList->child[1];
        }
    } else {
        structAttribute = new_struct_attribute(0);
    }
    int result = variable_scope_check(currentTable, structID, "struct");
    if (result == 1) {
        fprintf(out, "Error type 15 at Line %d: redeﬁne the same structure type\n", specifier->row);
    } else {
        sort_struct_attribute_varDec(structAttribute);
        put_node(structID, "struct", structAttribute, currentScopeNumber, 0, NULL);
    }
    return structAttribute;
}

int put_para_or_var(ASTNode *specifier, ASTNode *varDec, int para) {
    char *ID;
    int dimension = 0;
    Parameter *parameter = new_parameter();
    int *dimensions;
    // get ID and dimension
    if (varDec->child_count == 1) {
        // ID
        ID = varDec->child[0]->value;
    } else {
        // VarDec LB INT RB
        ASTNode *node = varDec;
        while(node->child_count == 4) {
            dimension++;
            node = node->child[0];
        }
        ID = node->child[0]->value;
        int index;
        node = varDec;
        int *arr = (int *)malloc(sizeof(int) * dimension);
        for (index = dimension - 1; index >= 0; index --) {
            *(arr + index) = atoi(node->child[2]->value);
            node = node->child[0];
        }
        dimensions = arr;
    }
    char *type;
    StructAttribute *structAttribute;
    // specifier: TYPE | StructSpecifier
    if (strcmp(specifier->type, "TYPE") == 0) {
        type = specifier->value;
    } else {
        // StructSpecifier: STRUCT ID LC DefList RC | STRUCT ID
        type = "structVariable";
        if (specifier->child_count == 2) {
            char *structID = specifier->child[1]->value;
            // STRUCT ID
            TableItem *item = find_struct(currentTable, structID);
            if (item == NULL) {
                fprintf(out, "Error at Line %d: undifined struct \"%s\"\n", specifier->row, structID);
                return 1;
            } else {
                structAttribute = item->attribute;
            }
        } else {
            // STRUCT ID LC DefList RC
            if (para == 1) {
                fprintf(out, "Error at Line %d: define struct before parameter is not allowed\n", specifier->row);
                return 1;
            } else {
                structAttribute = put_struct_specifier(specifier);
            }
        }
    }
    int result = variable_scope_check(currentTable, ID, type);
    if (result == -1 || result == 1) {
        // already been used
        if (para) {
            fprintf(out, "Error at Line %d: parameter is redifined in the same function\n", varDec->row);
            return 1;
        } else {
            fprintf(out, "Error type 3 at Line %d: variable is redeﬁned in the same scope\n", varDec->row);
            return 1;
        }
    } else if (result == 0) {
        if (para) {
            parameter->dimension = dimension;
            parameter->dimensions = dimensions;
            parameter->type = type;
        }
        TableItem *item;
        if (strcmp(type, "structVariable") == 0) {
            // put struct here
            item = put_node(ID, "structVariable", structAttribute, currentScopeNumber, dimension, dimensions);
            // IR end
            if (para) {
                parameter->attribute = structAttribute;
            } else {
                // struct variable declare space IR start
                int *dec_num = (int *)malloc(sizeof(int));
                *dec_num = structAttribute->varNum * 4;
                IRInstruct *dec_instruct = append_new_instruct(blockEnd);
                dec_instruct->type = _DECLARE;
                dec_instruct->result = item->varNum;
                dec_instruct->argOne = dec_num;
                // IR end
                // array of struct?
            } 
        } else {
            // put variable here
            item = put_node(ID, type, NULL, currentScopeNumber, dimension, dimensions);
            if (dimension > 0) {
                // array variable declarae space IR start
                int *dec_num = (int *)malloc(sizeof(int));
                int i;
                *dec_num = 1;
                for (i = 0; i < dimension; i++)
                    *dec_num *= *(dimensions + i);
                *dec_num = *dec_num * 4;
                IRInstruct *dec_instruct = append_new_instruct(blockEnd);
                dec_instruct->type = _DECLARE;
                dec_instruct->result = item->varNum;
                dec_instruct->argOne = dec_num;
                // IR end
            }
        }
        if (para) {
            parameter->item = item;
            // parameter IR start
            IRInstruct *para_instruct = append_new_instruct(blockEnd);
            para_instruct->type = _PARAMETER;
            para_instruct->result = item->varNum;
            // IR end
            append_new_parameter(currentFunction, parameter);
        }
    }
    return 0;
}

int put_var(ASTNode *currentSpecifier, ASTNode *varDec) {
    return put_para_or_var(currentSpecifier, varDec, 0);
}

void put_para(ASTNode *specifier, ASTNode *varDec) {
    put_para_or_var(specifier, varDec, 1);
}

typedef struct TypeCheck {
    int dimension;
    int *dimensions;
    int index;
    char *type;
    int r;
    StructAttribute *attribute;
    int *argNum;
    enum ArgType argType;
    ArrayList *trueList;
    ArrayList *falseList;
} TypeCheck;

TypeCheck *new_type_check() {
    TypeCheck *typeCheck = (TypeCheck *)malloc(sizeof(TypeCheck));
    typeCheck->dimension = 0;
    typeCheck->dimensions = NULL;
    typeCheck->type = NULL;
    typeCheck->attribute = NULL;
    typeCheck->r = 0;
    typeCheck->index = 0;
    typeCheck->trueList = NULL;
    typeCheck->falseList = NULL;
    return typeCheck;
}

TypeCheck *check_member(StructAttribute *attribute, char *ID) {
    if (attribute == NULL)
        return NULL;
    int index = 0;
    for (index = 0; index < attribute->varNum; index++) {
        StructVariable *variable = attribute->varDec[index];
        if (variable != NULL) {
            if (strcmp(variable->ID, ID) == 0) {
                TypeCheck *newType = new_type_check();
                newType->type = variable->type;
                newType->dimension = variable->dimension;
                newType->attribute = variable->attribute;
                newType->index = index;
                return newType;
            }
        }
    }
    return NULL;
}

void get_array_value(TypeCheck *typeCheck) {
    IRInstruct *value_instruct = append_new_instruct(blockEnd);
    value_instruct->type = _VALUE;
    value_instruct->argOne = typeCheck->argNum;
    value_instruct->argOneType = typeCheck->argType;
    value_instruct->result = new_temp_num();
    typeCheck->argNum = value_instruct->result;
    typeCheck->argType = _VAR_OR_TEMP;
}

TypeCheck* travel_exp(ASTNode *exp) {
    TypeCheck *typeCheck = new_type_check();
    if (exp->child_count == 1) {
        char *type = exp->child[0]->type;
        if (strcmp(type, "INT") == 0) {
            typeCheck->type = "int";
            typeCheck->r = 1;
            // int IR start
            typeCheck->argNum = (int *)malloc(sizeof(int));
            *typeCheck->argNum = atoi(exp->child[0]->value);
            typeCheck->argType = _CONSTANT;
            // IR end
        } else if (strcmp(type, "FLOAT") == 0) {
            typeCheck->type = "float";
            typeCheck->r = 1;
            // float IR start
            // IR end
        } else if (strcmp(type, "CHAR") == 0) {
            typeCheck->type = "char";
            typeCheck->r = 1;
            // char IR start
            // IR end
        } else {
            // ID
            char *ID = exp->child[0]->value;
            TableItem *item = find_variable(currentTable, ID);
            if (item == NULL) {
                fprintf(out, "Error type 1 at Line %d: variable is used without deﬁnition\n", exp->row);
                return NULL;
            } else {
                typeCheck->type = item->type;
                typeCheck->dimension = item->dimension;
                typeCheck->dimensions = item->dimensions;
                if (strcmp(item->type, "structVariable") == 0) {
                    typeCheck->attribute = item->attribute;
                } else {
                    typeCheck->attribute = NULL;
                }
                // struct or ID IR start
                typeCheck->argNum = item->varNum;
                if (typeCheck->dimension || strcmp(item->type, "structVariable") == 0)
                    typeCheck->argType = _ADDRESS;
                else
                    typeCheck->argType = _VAR_OR_TEMP;
                // IR end
            }
        }
        return typeCheck;
    } else if (exp->child_count == 2) {
        // MINUS Exp | NOT Exp
        if (strcmp(exp->child[0]->type, "MINUS") == 0) {
            TypeCheck *right = travel_exp(exp->child[1]);
            if (right == NULL) {
                return NULL;
            }
            if (strcmp(right->type, "int") == 0 || strcmp(right->type, "float") == 0) {
                if (right->dimension == 0) {
                    // MINUS IR start
                    if (right->dimension)
                        get_array_value(right);
                    IRInstruct *minus_instruct = append_new_instruct(blockEnd);
                    minus_instruct->type = _MINUS;
                    minus_instruct->result = new_temp_num();
                    minus_instruct->argOne = right->argNum;
                    minus_instruct->argOneType = right->argType;
                    right->argNum = minus_instruct->result;
                    right->argType = _VAR_OR_TEMP;
                    // IR end
                    return right;
                }
            }
            fprintf(out, "Error type 7 at Line %d: unmatching operands\n", exp->row);
            return NULL;
        } else {
            // NOT Exp
            TypeCheck *right = travel_exp(exp->child[1]);
            if (right == NULL) {
                return NULL;
            }
            if (strcmp(right->type, "int") == 0 && right->dimension == 0) {
                // NOT IR start
                ArrayList *temp = right->trueList;
                right->trueList = right->falseList;
                right->falseList = temp;
                // IR end
                return right;
            }
            fprintf(out, "Error at Line %d: only int variables can do boolean operation\n", exp->row);
            return NULL;
        }
    } else if (exp->child_count == 3) {
        if (exp->child[0]->child_count == 0) {
            // LP Exp RP | ID LP RP 
            if (strcmp(exp->child[0]->type, "LP") == 0) {
                return travel_exp(exp->child[1]);
            } else if (strcmp(exp->child[0]->type, "READ") == 0) {
                // READ LP RP
                // read IR start
                IRInstruct *read_instruct = append_new_instruct(blockEnd);
                read_instruct->type = _READ;
                read_instruct->result = new_temp_num();
                TypeCheck *newType = new_type_check();
                newType->type = "int";
                newType->argNum = read_instruct->result;
                newType->argType = _VAR_OR_TEMP;
                // IR end
                return newType;
            } else {
                char *ID = exp->child[0]->value;
                //ID LP RP
                TableItem *item = find_variable(currentTable, ID);
                if (item == NULL) {
                    fprintf(out, "Error type 2 at Line %d: function is invoked without deﬁnition\n", exp->row);
                    return NULL;
                } else {
                    if (strcmp(item->type, "function") == 0) {
                        FunctionAttribute *attribute = item->attribute;
                        if (attribute->parameters->memberNum == 0) {
                            typeCheck->type = attribute->returnType;
                            if (strcmp(typeCheck->type, "structVariable") == 0) {
                                typeCheck->attribute = attribute->attribute;
                            }
                            // non-arg function call IR start
                            IRInstruct *non_arg_instruct = append_new_instruct(blockEnd);
                            non_arg_instruct->type = _CALL;
                            non_arg_instruct->funcName = item->ID;
                            non_arg_instruct->result = new_temp_num();
                            typeCheck->argNum = non_arg_instruct->result;
                            typeCheck->argType = _VAR_OR_TEMP;
                            // IR end
                            return typeCheck;
                        } else {
                            fprintf(out, "Error type 9 at Line %d: the function’s arguments mismatch the declared parameters\n", exp->row);
                            return NULL;
                        }
                    } else {
                        fprintf(out, "Error type 11 at Line %d: applying function invocation operator on non-function names\n", exp->row);
                        return NULL;
                    }
                }
            }
        } else {
            // Exp OPP Exp | Exp DOT ID
            char *type = exp->child[1]->type;
            if (strcmp(type, "DOT") == 0) {
                TypeCheck *left = travel_exp(exp->child[0]);
                if (left == NULL)
                    return NULL;
                char *ID = exp->child[2]->value;
                if (strcmp(left->type, "structVariable")) {
                    fprintf(out, "Error type 13 at Line %d: accessing member of non-structure variable\n", exp->row);
                    return NULL;
                }
                TypeCheck *checkMenber = check_member(left->attribute, ID);
                if (checkMenber == NULL) {
                    fprintf(out, "Error type 14 at Line %d: accessing an undeﬁned structure member\n", exp->row);
                    return NULL;
                } else {
                    int *offset = (int *)malloc(sizeof(int));
                    *offset = checkMenber->index * 4;
                    IRInstruct *address_instruct = append_new_instruct(blockEnd);
                    address_instruct->type = _PLUS;
                    address_instruct->argOne = left->argNum;
                    address_instruct->argOneType = _ADDRESS;
                    address_instruct->argTwo = offset;
                    address_instruct->argTwoType = _CONSTANT;
                    address_instruct->result = new_temp_num();
                    checkMenber->index = 0;
                    checkMenber->argNum = address_instruct->result;
                    checkMenber->argType = _VALUE;
                    return checkMenber;
                }
            } else {
                TypeCheck *left = travel_exp(exp->child[0]);
                if (left == NULL)
                    return NULL;
                // backpatching block IR start
                IRBlock *nextBlock;
                if (strcmp(type, "AND") == 0 || strcmp(type, "OR") == 0)
                    nextBlock = append_new_block();
                TypeCheck *right = travel_exp(exp->child[2]);
                if (right == NULL)
                    return NULL;
                if (strcmp(type, "ASSIGN") == 0) {
                    _assign = 1;
                    if (left->r) {
                        fprintf(out, "Error type 6 at Line %d: rvalue on the left side of assignment operator\n", exp->row);
                    }
                    if (strcmp(left->type, right->type) == 0 && left->dimension == right->dimension) {
                        if (strcmp(left->type, "structVariable") == 0) {
                            if (compare_if_equal(left->attribute, right->attribute) == 0) {
                                // unmatch
                                fprintf(out, "Error type 5 at Line %d: unmatching types on both sides of assignment operator (=)\n", exp->row);
                                return NULL;
                            }
                            // match
                            // assign struct IR start
                            // IR end
                            return left;
                        } else {
                            // match
                            // assign IR start
                            IRInstruct *assign_instruct = append_new_instruct(blockEnd);
                            if (left->argType == _VALUE)
                                assign_instruct->type = _COPY;
                            else
                                assign_instruct->type = _ASSIGN;
                            assign_instruct->result = left->argNum;
                            assign_instruct->argOne = right->argNum;
                            assign_instruct->argOneType = right->argType;
                            // IR end
                            return left;
                        }
                    } else {
                        fprintf(out, "Error type 5 at Line %d: unmatching types on both sides of assignment operator (=)\n", exp->row);
                        return NULL;
                    }
                } else if (strcmp(type, "AND") == 0 || strcmp(type, "OR") == 0) {
                    // boolean expression
                    if (strcmp(left->type, "int") == 0 && left->dimension == 0 && strcmp(right->type, "int") == 0 && right->dimension == 0) {
                        // valid
                        TypeCheck *newType = new_type_check();
                        newType->type = left->type;
                        newType->dimension = left->dimension;
                        if (left->r || right->r)
                            newType->r = 1;
                        // boolean expression IR start
                        if (strcmp(type, "AND") == 0) {
                            back_patching_true_list(left->trueList, nextBlock);
                            newType->trueList = right->trueList;
                            newType->falseList = merge_list(left->falseList, right->falseList);
                        } else {
                            back_patching_false_list(left->falseList, nextBlock);
                            newType->falseList = right->falseList;
                            newType->trueList = merge_list(left->trueList, right->trueList);
                        }
                        // IR end
                        return newType;
                    } else {
                        // invalid
                        fprintf(out, "Error at Line %d: only int variables can do boolean operation\n", exp->row);
                        return NULL;
                    }
                } else if (strcmp(type, "LT") == 0 || strcmp(type, "LE") == 0 || strcmp(type, "GT") == 0 || strcmp(type, "GE") == 0
                    || strcmp(type, "EQ") == 0 || strcmp(type, "NE") == 0) {
                    // comparation
                    if (strcmp(type, "EQ") == 0 || strcmp(type, "NE") == 0) {
                         if (!strcmp(left->type, right->type) == 0 || !left->dimension == right->dimension) {
                            fprintf(out, "Error at Line %d: comparation on differnt type is not allowed\n", exp->row);
                            return NULL;
                        }
                        if (strcmp(left->type, "structVariable") == 0 && compare_if_equal(left->attribute, right->attribute) == 0) {
                            fprintf(out, "Error at Line %d: comparation on differnt type is not allowed\n", exp->row);
                            return NULL;
                        }
                    } else {
                        if (left->dimension != 0 || right->dimension != 0) {
                            fprintf(out, "Error at Line %d: comparation on array is not allowed\n", exp->row);        
                            return NULL;
                        } else if (strcmp(left->type, "structVariable") == 0 || strcmp(right->type, "structVariable") == 0) {
                            fprintf(out, "Error at Line %d: comparation on struct is not allowed\n", exp->row);
                            return NULL;
                        }
                    }
                    TypeCheck *newType = new_type_check();
                    newType->type = "int";
                    if (left->r || right->r)
                        newType->r = 1;
                    // comparation IR start
                    if (blockEnd->instructNum)
                        append_new_block();
                    if (left->index)
                        get_array_value(left);
                    if (right->index)
                        get_array_value(right);
                    IRInstruct *comparation_instruct = append_new_instruct(blockEnd);
                    if (strcmp(type, "LT") == 0)
                        comparation_instruct->type = _LESSTHAN;
                    else if (strcmp(type, "LE") == 0)
                        comparation_instruct->type = _LESSEQUAL;
                    else if (strcmp(type, "GT") == 0)
                        comparation_instruct->type = _GREATERTHAN;
                    else if (strcmp(type, "GE") == 0)
                        comparation_instruct->type = _GREATEREQUAL;
                    else if (strcmp(type, "EQ") == 0)
                        comparation_instruct->type = _EQUAL;
                    else
                        comparation_instruct->type = _NOTEQUAL;
                    comparation_instruct->argOne = left->argNum;
                    comparation_instruct->argOneType = left->argType;
                    comparation_instruct->argTwo = right->argNum;
                    comparation_instruct->argTwoType = right->argType;
                    newType->trueList = new_array_list();
                    append_to_array_list(newType->trueList, blockEnd);
                    newType->falseList = new_array_list();
                    append_to_array_list(newType->falseList, blockEnd);
                    // IR end
                    return newType;
                } else if (strcmp(type, "PLUS") == 0 || strcmp(type, "MINUS") == 0 || strcmp(type, "MUL") == 0 ||
                strcmp(type, "DIV") == 0) {
                    // int & float
                    if (left->dimension == 0 && right->dimension == 0 && strcmp(left->type, "structVariable") && strcmp(right->type, "structVariable") &&
                    strcmp(left->type, "char") && strcmp(right->type, "char")) {
                        TypeCheck *newType = new_type_check();
                        if (strcmp(left->type, "int") == 0 && strcmp(right->type, "int") == 0) {
                            newType->type = "int";
                        } else {
                            newType->type = "float";
                        }
                        if (left->r || right->r)
                            newType->r = 1;
                        if (left->index)
                            get_array_value(left);
                        if (right->index)
                            get_array_value(right);
                        // Arithmetic opeartion IR start
                        IRInstruct *arithmetic_instruct = append_new_instruct(blockEnd);
                        if (strcmp(type, "PLUS") == 0)
                            arithmetic_instruct->type = _PLUS;
                        else if (strcmp(type, "MINUS") == 0)
                            arithmetic_instruct->type = _SUBSTRACT;
                        else if (strcmp(type, "MUL") == 0)
                            arithmetic_instruct->type = _MULTIPLY;
                        else
                            arithmetic_instruct->type = _DIVIDE;
                        arithmetic_instruct->result = new_temp_num();
                        arithmetic_instruct->argOne = left->argNum;
                        arithmetic_instruct->argOneType = left->argType;
                        arithmetic_instruct->argTwo = right->argNum;
                        arithmetic_instruct->argTwoType = right->argType;
                        newType->argNum = arithmetic_instruct->result;
                        newType->argType = _VAR_OR_TEMP;
                        // IR end
                        return newType;
                    } else {
                        fprintf(out, "Error type 7 at Line %d: unmatching operands\n", exp->row);
                        return NULL;
                    }
                }
            }
        }
    } else {
        if (strcmp(exp->child[0]->type, "ID") == 0) {
            // ID LP Args RP
            // call function
            char *ID = exp->child[0]->value;
            TableItem *item = find_variable(currentTable, ID);
            if (item == NULL) {
                fprintf(out, "Error type 2 at Line %d: function is invoked without deﬁnition\n", exp->row);
                return NULL;
            } else {
                if (strcmp(item->type, "function") == 0) {
                    FunctionAttribute *attribute = item->attribute;
                    if (attribute->parameters->memberNum == 0) {
                        fprintf(out, "Error type 9 at Line %d: the function’s arguments mismatch the declared parameters\n", exp->row);
                        return NULL;
                    } else {
                        ASTNode *args = exp->child[2];
                        int judge = 0;
                        int i = 0;
                        ArrayList *typeCheckArrayList = new_array_list();
                        int totalParaNum = attribute->parameters->memberNum;
                        while(i < totalParaNum) {
                            Parameter *parameter = attribute->parameters->arr[i];
                            TypeCheck *c = travel_exp(args->child[0]);
                            append_to_array_list(typeCheckArrayList, c);
                            if (c == NULL) {
                                return NULL;
                            }
                            if (strcmp(c->type, parameter->type)) {
                                judge = 1;
                                break;
                            } else {
                                if (strcmp(c->type, "structVariable") == 0 && compare_if_equal(c->attribute, parameter->attribute) == 0) {
                                    judge = 1;
                                    break;
                                } 
                            }
                            i++;
                            if (args->child_count == 3) {
                                args = args->child[2];
                                if (i >= attribute->parameters->memberNum) {
                                    judge = 1;
                                    break;
                                }
                            } else {
                                if (i < attribute->parameters->memberNum) {
                                    judge = 1;
                                }
                                break;
                            }
                        }
                        if (judge) {
                            fprintf(out, "Error type 9 at Line %d: the function’s arguments mismatch the declared parameters\n", exp->row);
                            free_array_list(typeCheckArrayList);
                            return NULL;
                        } else {
                            typeCheck->type = attribute->returnType;
                            if (strcmp(typeCheck->type, "structVariable") == 0) {
                                typeCheck->attribute = attribute->attribute;
                            }
                            // arg function call IR start
                            int i;
                            for (i = typeCheckArrayList->memberNum - 1; i >= 0; i--) {
                                TypeCheck *input_para = typeCheckArrayList->arr[i];
                                IRInstruct *arg_instruct = append_new_instruct(blockEnd);
                                arg_instruct->type = _ARGUMENT;
                                arg_instruct->argOne = input_para->argNum;
                                arg_instruct->argOneType = input_para->argType;
                            }
                            IRInstruct *call_instruct = append_new_instruct(blockEnd);
                            call_instruct->type = _CALL;
                            call_instruct->funcName = item->ID;
                            call_instruct->result = new_temp_num();
                            typeCheck->argNum = call_instruct->result;
                            typeCheck->argType = _VAR_OR_TEMP;
                            free_array_list(typeCheckArrayList);
                            // IR end
                            return typeCheck;
                        }
                    }
                } else {
                    fprintf(out, "Error type 11 at Line %d: applying function invocation operator on non-function names\n", exp->row);
                    return NULL;
                }
            }
        } else if (strcmp(exp->child[0]->type, "Exp") == 0) {
            // array
            // Exp LB Exp RB
            TypeCheck *left = travel_exp(exp->child[0]);
            TypeCheck *right = travel_exp(exp->child[2]);
            if (left == NULL || right == NULL)
                return NULL;
            // check right Exp
            if (strcmp(right->type, "int") || right->dimension) {
                fprintf(out, "Error type 12 at Line %d: array indexing with non-integer type expression\n", exp->row);
                return NULL;
            }
            if (left->dimension == 0) {
                fprintf(out, "Error type 10 at Line %d: applying indexing operator ([...]) on non-array type variables\n", exp->row);
                return NULL;
            }
            // array IR start
            int i;
            int arrayDimension = left->index + left->dimension;
            int *offset = (int *)malloc(sizeof(int));
            *offset = 1;
            for (i = left->index + 1; i < arrayDimension; i++) {
                *offset *= *(left->dimensions + i);
            }
            *offset *= 4;
            int *argTwo;
            enum ArgType argTwoType;
            if (right->argType == _CONSTANT) {
                *offset *= *right->argNum;
                argTwo = offset;
                argTwoType = _CONSTANT;
            } else {
                IRInstruct *mul_instruct = append_new_instruct(blockEnd);
                mul_instruct->type = _MULTIPLY;
                mul_instruct->argOne = right->argNum;
                mul_instruct->argOneType = right->argType;
                mul_instruct->argTwo = offset;
                mul_instruct->argTwoType = _CONSTANT;
                mul_instruct->result = new_temp_num();
                argTwo = mul_instruct->result;
                argTwoType = _VAR_OR_TEMP;
            }
            IRInstruct *plus_instruct = append_new_instruct(blockEnd);
            plus_instruct->type = _PLUS;
            plus_instruct->argOne = left->argNum;
            plus_instruct->argOneType = left->argType;
            plus_instruct->argTwo = argTwo;
            plus_instruct->argTwoType = argTwoType;
            plus_instruct->result = new_temp_num();
            left->argNum = plus_instruct->result;
            left->argType = _VAR_OR_TEMP;
            left->index++;
            left->dimension--;
            if (left->dimension == 0)
                left->argType = _VALUE;
            // IR end
            return left;
        } else {
            // WRITE LP Exp RP
            // IR start
            TypeCheck *check = travel_exp(exp->child[2]);
            IRInstruct *write_instruct = append_new_instruct(blockEnd);
            write_instruct->type = _WRITE;
            write_instruct->argOne = check->argNum;
            write_instruct->argOneType = check->argType;
            // IR end
            return NULL;
        }
    }
}

void check_assign_exp(ASTNode *varDec, ASTNode *exp) {
    TypeCheck *typeCheck = travel_exp(exp);
    if (typeCheck != NULL) {
        while(varDec->child_count == 4) {
            varDec = varDec->child[0];
        }
        char *ID = varDec->child[0]->value;
        TableItem *item = find_variable(currentTable, ID);
        if (strcmp(item->type, typeCheck->type) == 0 && item->dimension == typeCheck->dimension) {
            if (strcmp(item->type, "structVariable") == 0 && compare_if_equal(item->attribute, typeCheck->attribute) == 0) {
                fprintf(out, "Error type 5 at Line %d: unmatching types on both sides of assignment operator (=)\n", exp->row);
                return;
            }
        } else {
            fprintf(out, "Error type 5 at Line %d: unmatching types on both sides of assignment operator (=)\n", exp->row);
            return;
        }
        // assign IR start
        IRInstruct *assign_instruct = append_new_instruct(blockEnd);
        assign_instruct->type = _ASSIGN;
        assign_instruct->result = item->varNum;
        assign_instruct->argOne = typeCheck->argNum;
        assign_instruct->argOneType = typeCheck->argType;
        // IR end
    }
}

void check_exp(ASTNode *exp) {
    travel_exp(exp);
}

TypeCheck *check_condition(ASTNode *exp) {
    _assign = 0;
    TypeCheck *type = travel_exp(exp);
    if (type != NULL) {
        if (!(strcmp(type->type, "int") == 0 && type->dimension == 0)) {
            fprintf(out, "Error at Line %d: the result of condition must be int\n", exp->row);
        } else if (_assign) {
            fprintf(out, "Error at Line %d: assignment in condition is not allowed\n", exp->row);
        }
    }
    return type;
}

void check_return_exp(ASTNode *exp) {
    char *returnType = currentFunction->returnType;
    StructAttribute *attribute = currentFunction->attribute;
    // int dimension = currentFunction->dimension;
    TypeCheck *check = travel_exp(exp);
    if (check == NULL) {
        return;
    }
    if (strcmp(check->type, returnType)) {
        fprintf(out, "Error type 8 at Line %d: the function’s return value type mismatches the declared type\n", exp->row);
    // } else if (type->dimension != dimension) {
    //     fprintf(out, "Error at Line %d: return value type dimension mismatches\n", exp->row);
    } else {
        if (strcmp(check->type, "structVariable") == 0 && compare_if_equal(check->attribute, attribute) == 0) {
            fprintf(out, "Error type 8 at Line %d: the function’s return value type mismatches the declared type\n", exp->row);
        }
    }
    // return IR start
    IRInstruct *return_instruct = append_new_instruct(blockEnd);
    return_instruct->type = _RETURN;
    return_instruct->argOne = check->argNum;
    return_instruct->argOneType = check->argType;
    // IR end
}