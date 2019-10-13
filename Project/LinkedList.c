#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct LstHead
{
    int num;
    struct LstNode *next;
} LstHead;

typedef struct LstNode
{
    char *name;
    char *text;
    int name_len;
    int semi;
    struct LstNode *next;
    struct ArgHead *argHead;
} LstNode;

typedef struct ArgHead
{
    int num;
    struct Arg *next;
} ArgHead;

typedef struct Arg
{
    char *id;
    struct Arg *next;
    char *match;
} Arg;

ArgHead *newArgHead()
{
    ArgHead *argHead = (ArgHead *)malloc(sizeof(ArgHead));
    argHead->num = 0;
    argHead->next = NULL;
}

Arg *newArg(char *id)
{
    Arg *arg = (Arg *)malloc(sizeof(Arg));
    arg->id = id;
    arg->next = NULL;
    arg->match = NULL;
}

LstHead *newLstHead()
{
    LstHead *head = (LstHead *)malloc(sizeof(LstHead));
    head->num = 0;
    head->next = NULL;
}

LstNode *newLstNode()
{
    LstNode *node = (LstNode *)malloc(sizeof(LstNode));
    node->name = NULL;
    node->text = NULL;
    node->next = NULL;
    node->semi = 0;
    node->name_len = 0;
    node->argHead = newArgHead();
    return node;
}

void appendNode(LstHead *head, LstNode *node)
{
    if(head->next == NULL){
        head->next = node;
    }else{
        LstNode *tmp = head->next;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    head->num++;
}

void appendArg(ArgHead *argHead, Arg *arg)
{
    if(argHead->next == NULL){
        argHead->next = arg;
    }else{
        Arg *tmp = argHead->next;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = arg;
    }
    argHead->num++;
}

void appendArgId(ArgHead *argHead, char* id)
{
    appendArg(argHead, newArg(id));
}

int checkArg(ArgHead *head, char* id){
    Arg *arg = head->next;
    while(arg != NULL){
        if(!strcmp(arg->id, id)){
            return 1;
        }
        arg = arg->next;
    }
    return 0;
}

void clearMatch(ArgHead *argHead){
    Arg *arg = argHead->next;
    while(arg != NULL){
        arg->match = NULL;
        arg = arg->next;
    }
}

void printfLstNode(LstNode *node)
{
    printf("Name: %s \nText: %s\n", node->name,node->text);
}

void printfArg(Arg *arg)
{
    printf("id: %s\n", arg->id);
}

void printfAll(LstNode *node)
{
    printfLstNode(node);
    if(node->next != NULL){
        printfAll(node->next);
    }
}

void printfAllArg(Arg *arg)
{
    printfArg(arg);
    if(arg->next != NULL){
        printfAllArg(arg->next);
    }
}

void printfLst(LstHead *head)
{
    printfAll(head->next);
}

void printfArgs(ArgHead *argHead)
{
    printfAllArg(argHead->next);
}

char *splice_(char* a, char* b)
{
    char *str = malloc(strlen(a) + strlen(b) + 1);
    strcpy(str, a);
    strcat(str, b);
    str[strlen(a) + strlen(b)] = 0;
    return str;
}

char *replace(char *str, ArgHead *argHead){
    int count;
    int match = 0;
    int left = -1;
    int id = 0;
    for (count = 0; count < strlen(str); count++)
    {
        int i;
        Arg *tmp = argHead->next;
        if(left == -1){
            if(str[count] == '('){
                left = count;
            }
        }else if(left != -1){
            if(str[count] == '('){
                left = count;
            }else if(str[count] == ',' || str[count] == ')' || str[count] == '+' || str[count] == '-' || str[count] == '*'
            || str[count] == '/' || str[count] == '-' || str[count] == '<' || str[count] == '>' ||
             (count + 1 < strlen(str) && 
             ((str[count] == '|' && str[count + 1] == '|') || (str[count] == '&' && str[count + 1] == '&')))){
                if(id == 0){
                    left = -1;
                    continue;
                }else{
                    char *content = malloc(count - left);
                    content[count - left - 1] = 0;
                    int x;
                    for (x = left + 1; x < count; x++){
                        content[x - left - 1] = str[x];
                    }
                    for (x = count - left - 2; x >= 0;  x--){
                        if(content[x] == ' '){
                            content[x] = 0;
                        }else{
                            break;
                        }
                    }
                    int y;
                    Arg *arg = argHead->next;
                    int next = count - 1;
                    int match = 0;
                    for (y = 0; y < argHead->num; y++){
                        if(!strcmp(arg->id, content)){
                            char *front = malloc(left + 1);
                            front[left] = 0;
                            int a;
                            for (a = 0; a < left; a++){
                                front[a] = str[a];
                            }
                            front = splice_(front, arg->match);
                            char *behind = malloc(strlen(str) - count);
                            behind[strlen(str) - count - 1] = 0;
                            for (a = count + 1; a < strlen(str); a++){
                                behind[a - count - 1] = str[a];
                            }
                            str = splice_(front, behind);
                            next = left + strlen(arg->match);
                            match = 1;
                            break;
                        }
                        arg = arg->next;
                    }
                    id = 0;
                    if(str[next + 1] == '|'){
                        next += 2;
                    }
                    if((next + 2 < strlen(str)) && (str[next + 1] == '>' || str[next + 1] == '<') && str[next + 2] == '='){
                        next += 2;
                    }
                    if(str[next + 1] == ')'){
                        left = -1;
                        count = next;
                    }else{
                        left = next + 1;
                        count = next + 1;
                    }
                }
            }else if(str[count] == ' ' && id == 0){
                left++;
            }else{
                id = 1;
            }
        }
        
    }
    return str;
}
// int main(){
//     ArgHead *head = (ArgHead *)malloc(sizeof(ArgHead));
//     head->num = 2;
//     Arg *arg1 = newArg("xcdcw");
//     head->next = arg1;
//     Arg *arg2 = newArg("ycdski");
//     arg1->match = "aa";
//     arg2->match = "bb";
//     arg1->next = arg2;
//     char *str = "(xcdcw) = ( ((xcdcw <= ycdski) >= (ycdski) || (xcdcw))||(xcdcw)) + (ycdski);(ycdski)";
//     printf(replace(str, head));
// }
// int main()
// {
//     LstHead *head = newLstHead();
//     LstNode *node0 = newLstNode("hello()", "printf(\"hello world\")");
//     LstNode *node1 = newLstNode("test()", "printf(\"test\")");
//     LstNode *node2 = newLstNode("node1()", "printf(\"node1\")");
//     LstNode *node3 = newLstNode("node2()", "printf(\"node2\")");
//     appendNode(head, node0);
//     printfLst(head);
//     appendNode(head, node1);
//     appendNode(head, node2);
//     appendNode(head, node3);
//     printfLst(head);
//     LstNode **lst = getLst(head);
//     printf("%d", head->num);
//     printf("%s", lst[1]->name);
//     printf("END");
// }

// int main()
// {
//     ArgHead *head = newArgHead();
//     printf("%d", head->num);
//     Arg *arg1 = newArg("x");
//     Arg *arg2 = newArg("yz");
//     Arg *arg3 = newArg("xdsf");
//     Arg *arg4 = newArg("fwe");
//     appendArg(head, arg1);
//     appendArg(head, arg2);
//     appendArg(head, arg3);
//     appendArg(head, arg4);
//     printfArgs(head);
//     printf("%d", head->num);
//     if(checkArg(head, "yzds"))
//         printf("REJECT");
// }