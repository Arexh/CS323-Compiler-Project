#include <stdlib.h>
#include <stdio.h>

enum ArgType
{
    CONSTANT = 1, VAR_OR_TEMP
};

enum InstructType
{
    ASSIGN = 1, PLUS, MINUS, MULTIPLY, SUBSTRACT, DIVIDE, ADDRESS, COPY, RETURN, DECLARE, PARAMETER, ARGUMENT, CALL, READ, WRITE, FUNCTION,
    LESSTHAN, LESSEQUAL, GREATERTHAN, GREATEREQUAL, NOTEQUAL, EQUAL
};

typedef struct IRInstruct {
    int arg_one;
    int arg_two;
    int result;
    char *func_name;
    enum InstructType type;
    enum ArgType arg_one_type;
    enum ArgType arg_two_type;
    struct IRInstruct *next;
    struct IRInstruct *previous;
} IRInstruct;

IRInstruct *new_IR_instruct() {
    IRInstruct *instruct = (IRInstruct *)malloc(sizeof(IRInstruct));
    instruct->arg_one = 0;
    instruct->arg_two = 0;
    instruct->result = 0;
    instruct->next = NULL;
    instruct->previous = NULL;
    instruct->func_name = NULL;
}

void get_result_string(char str[32], int num) {
    if (num > 0)
        sprintf(str, "v%d", num);
    else
        sprintf(str, "t%d", num);
}

void get_arg_string(char str[32], int num, enum ArgType type) {
    if (type == CONSTANT)
        sprintf(str, "#%d", num);
    else
        get_result_string(str, num);
}

void get_IR_instruct_string(char str[128], IRInstruct *instruct) {
    char result[32], arg_one[32], arg_two[32];
    get_result_string(result, instruct->result);
    get_arg_string(arg_one, instruct->arg_one, instruct->arg_one_type);
    get_arg_string(arg_two, instruct->arg_two, instruct->arg_two_type);
    switch(instruct->type) {
        case ASSIGN:
            sprintf(str, "%s := %s", result, arg_one);
            break;
        case PLUS:
            sprintf(str, "%s := %s + %s", result, arg_one, arg_two);
            break;
        case MINUS:
            sprintf(str, "%s := %s - %s", result, arg_one, arg_two);
            break;
        case MULTIPLY:
            sprintf(str, "%s := %s * %s", result, arg_one, arg_two);
            break;
        case SUBSTRACT:
            sprintf(str, "%s := %s - %s", result, arg_one, arg_two);
            break;
        case DIVIDE:
            sprintf(str, "%s := %s / %s", result, arg_one, arg_two);
            break;
        case ADDRESS:
            sprintf(str, "%s := &%s", result, arg_one);
            break;
        case COPY:
            sprintf(str, "*%s := %s", result, arg_one);
            break;
        case RETURN:
            sprintf(str, "RETURN %s", result);
            break;
        case DECLARE:
            sprintf(str, "DEC %s %d", result, instruct->arg_one);
            break;
        case PARAMETER:
            sprintf(str, "PARAM %s", result);
            break;
        case ARGUMENT:
            sprintf(str, "ARG %s", result);
            break;
        case CALL:
            sprintf(str, "%s := CALL %s", result, instruct->func_name);
            break;
        case READ:
            sprintf(str, "READ %s", result);
            break;
        case WRITE:
            sprintf(str, "WRITE %s", result);
            break;
        case FUNCTION:
            sprintf(str, "FUNCTION %s :", instruct->func_name);
            break;
        // reversed logic
        case LESSTHAN:
            sprintf(str, "IF %s >= %s GOTO", arg_one, arg_two);
            break;
        case LESSEQUAL:
            sprintf(str, "IF %s > %s GOTO", arg_one, arg_two);
            break;
        case GREATERTHAN:
            sprintf(str, "IF %s <= %s GOTO", arg_one, arg_two);
            break;
        case GREATEREQUAL:
            sprintf(str, "IF %s < %s GOTO", arg_one, arg_two);
            break;
        case EQUAL:
            sprintf(str, "IF %s != %s GOTO", arg_one, arg_two);
            break;
        case NOTEQUAL:
            sprintf(str, "IF %s == %s GOTO", arg_one, arg_two);
            break;
    }
}

// int main() {
//     IRInstruct *instruct = new_IR_instruct();
//     instruct->type = FUNCTION;
//     instruct->arg_one_type = CONSTANT;
//     char str[128];
//     get_IR_instruct_string(str, instruct);
//     printf("%s\n", str);
//     puts("END");
//     return 0;
// }