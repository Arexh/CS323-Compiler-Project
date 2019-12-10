#include <stdlib.h>
#include <stdio.h>

enum ArgType
{
    _CONSTANT = 1, _VAR_OR_TEMP
};

enum InstructType
{
    _ASSIGN = 1, _PLUS, _MINUS, _MULTIPLY, _SUBSTRACT, _DIVIDE, _ADDRESS, _COPY, _RETURN, _DECLARE, _PARAMETER, _ARGUMENT, _CALL, _READ, _WRITE, _FUNCTION,
    _LESSTHAN, _LESSEQUAL, _GREATERTHAN, _GREATEREQUAL, _NOTEQUAL, _EQUAL
};

typedef struct IRInstruct {
    int *argOne;
    int *argTwo;
    int *result;
    char *funcName;
    enum InstructType type;
    enum ArgType argOneType;
    enum ArgType argTwoType;
    struct IRInstruct *next;
    struct IRInstruct *previous;
} IRInstruct;

IRInstruct *new_IR_instruct() {
    IRInstruct *instruct = (IRInstruct *)malloc(sizeof(IRInstruct));
    instruct->argOne = NULL;
    instruct->argTwo = NULL;
    instruct->result = NULL;
    instruct->next = NULL;
    instruct->previous = NULL;
    instruct->funcName = NULL;
}

void get_result_string(char str[32], int *num) {
    if (num == NULL)
        return;
    if (*num > 0)
        sprintf(str, "v%d", *num);
    else
        sprintf(str, "t%d", -*num);
}

void get_arg_string(char str[32], int *num, enum ArgType type) {
    if (num == NULL)
        return;
    if (type == _CONSTANT)
        sprintf(str, "#%d", *num);
    else
        get_result_string(str, num);
}

void get_IR_instruct_string(char str[128], IRInstruct *instruct) {
    char result[32], argOne[32], argTwo[32];
    get_result_string(result, instruct->result);
    get_arg_string(argOne, instruct->argOne, instruct->argOneType);
    get_arg_string(argTwo, instruct->argTwo, instruct->argTwoType);
    switch(instruct->type) {
        case _ASSIGN:
            sprintf(str, "%s := %s", result, argOne);
            break;
        case _PLUS:
            sprintf(str, "%s := %s + %s", result, argOne, argTwo);
            break;
        case _MINUS:
            sprintf(str, "%s := #0 - %s", result, argOne);
            break;
        case _MULTIPLY:
            sprintf(str, "%s := %s * %s", result, argOne, argTwo);
            break;
        case _SUBSTRACT:
            sprintf(str, "%s := %s - %s", result, argOne, argTwo);
            break;
        case _DIVIDE:
            sprintf(str, "%s := %s / %s", result, argOne, argTwo);
            break;
        case _ADDRESS:
            sprintf(str, "%s := &%s", result, argOne);
            break;
        case _COPY:
            sprintf(str, "*%s := %s", result, argOne);
            break;
        case _RETURN:
            sprintf(str, "RETURN %s", result);
            break;
        case _DECLARE:
            sprintf(str, "DEC %s %d", result, *instruct->argOne);
            break;
        case _PARAMETER:
            sprintf(str, "PARAM %s", result);
            break;
        case _ARGUMENT:
            sprintf(str, "ARG %s", result);
            break;
        case _CALL:
            sprintf(str, "%s := CALL %s", result, instruct->funcName);
            break;
        case _READ:
            sprintf(str, "READ %s", result);
            break;
        case _WRITE:
            sprintf(str, "WRITE %s", result);
            break;
        case _FUNCTION:
            sprintf(str, "FUNCTION %s :", instruct->funcName);
            break;
        // reversed logic
        case _LESSTHAN:
            sprintf(str, "IF %s >= %s GOTO label", argOne, argTwo);
            break;
        case _LESSEQUAL:
            sprintf(str, "IF %s > %s GOTO label", argOne, argTwo);
            break;
        case _GREATERTHAN:
            sprintf(str, "IF %s <= %s GOTO label", argOne, argTwo);
            break;
        case _GREATEREQUAL:
            sprintf(str, "IF %s < %s GOTO label", argOne, argTwo);
            break;
        case _EQUAL:
            sprintf(str, "IF %s != %s GOTO label", argOne, argTwo);
            break;
        case _NOTEQUAL:
            sprintf(str, "IF %s == %s GOTO label", argOne, argTwo);
            break;
    }
}

// int main() {
//     IRInstruct *instruct = new_IR_instruct();
//     instruct->type = _FUNCTION;
//     instruct->arg_one_type = _CONSTANT;
//     char str[128];
//     get_IR_instruct_string(str, instruct);
//     printf("%s\n", str);
//     puts("END");
//     return 0;
// }