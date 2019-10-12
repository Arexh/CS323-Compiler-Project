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
    struct LstNode *next;
} LstNode;

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

void printfLstNode(LstNode *node)
{
    printf("Name: %s \nText: %s\n", node->name,node->text);
}

void printfAll(LstNode *node)
{
    printfLstNode(node);
    if(node->next != NULL){
        printfAll(node->next);
    }
}

void printfLst(LstHead *head)
{
    printfAll(head->next);
}

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