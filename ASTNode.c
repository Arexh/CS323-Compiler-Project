#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
FILE *fp;
FILE *out;
typedef struct ASTNode
{
    char *value;
    char *type;
    int child_count;
    int terminal;
    int row;
    struct ASTNode *sibling;
    struct ASTNode *child;
} ASTNode;

ASTNode *init()
{
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->value = NULL;
    node->type = NULL;
    node->child_count = 0;
    node->terminal = 0;
    node->row = 0;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

ASTNode *new(char* type, char* value, int terminal, int row)
{
    ASTNode *node = init();
    node->type = type;
    node->value = value;
    node->terminal = terminal;
    node->row = row;
    return node;
}

ASTNode *newLeaf(char* type, char* value)
{
    return new(type, value, 1, 0);
}

ASTNode *newNode(char* type, int row)
{
    return new(type, NULL, 0, row);
}

ASTNode *newNotation(char* type)
{
    return new(type, NULL, -1, 0);
}

void appendChild(ASTNode *father, int count, ...)
{
    va_list valist;
    va_start(valist, count);
    ASTNode *temp = father->child;
    int key = 0;
    while(temp != NULL && temp->sibling != NULL)
    {
        temp = temp->sibling;
    }
    if(temp == NULL) {
        father->child = va_arg(valist, ASTNode *);
        father->child_count = 1;
        temp = father->child;
        key = 1;
    }
    for(key; key < count; key++) {
        temp->sibling = va_arg(valist, ASTNode *);
        father->child_count++;
        temp = temp->sibling;
    }
}

void printfNode(ASTNode *node, int count)
{
    if(node->type != "NONE"){
        if(node->terminal == 1) {
            fprintf(out, "%*s%s: %s\n", count, "", node->type, node->value);
        } else if (node->terminal == 0) {
            fprintf(out, "%*s%s (%d)\n", count, "", node->type, node->row);
        } else {
            fprintf(out, "%*s%s\n", count, "", node->type);
        }
    }
}

void dfsPrintf(ASTNode *node, int count)
{   
    if(node == NULL)
        return;
    printfNode(node, count);
    dfsPrintf(node->child, count + 2);
    dfsPrintf(node->sibling, count);
}

// int main()
// {
//     ASTNode *node = newNode("Program", "1");
//     ASTNode *node1 = newNode("ExtDefList", "1");
//     ASTNode *node2 = newNode("ExtDef", "1");
//     ASTNode *node3 = newNode("Specifier", "1");
//     ASTNode *node4 = newLeaf("TYPE", "int");
//     ASTNode *node5 = newNotation("PLUS");
//     ASTNode *node6 = newNode("VarDec", "1");
//     ASTNode *node7 = newLeaf("ID", "global");
//     appendChild(node, 5, node1, node2, node3, node4, node5);
//     dfsPrintf(node, 0);
//     printf("END");
//     return 0;
// }
