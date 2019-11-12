#include "SymbolTable.c"

void program(ASTNode *node) {
    // ExtDefList
    extDefList(node->child[0]);
}

void extDefList(ASTNode *node) {
    if (node->child_count == 2) {
        // ExtDef ExtDefList
        extDef(node->child[0]);
        extDefList(node->child[1]);
    }
}

void extDef(ASTNode *node) {
    if (node->child->count == 3) {
        if (strcmp(node->child[1]->type, "ExtDecList")) {
            // Specifier ExtDecList SEMI: int a, b, c;
            specifier(node->child[0]);
            extDefList(node->child[1]);
        } else {
            // Specifier FunDec CompSt: int main() {}
            specifier(node->child[0]);
            funDec(node->child[1]);
            compSt(node->child[2]);
        }
    } else {
        // Specifier SEMI: int;
        specifier(node->child[0]);
    }
}

void extDefList(ASTNode *node) {
    if (node->child_count == 1) {
        // VarDec
        varDec(node->child[0]);
    } else {
        // VarDec COMMA ExtDecList: a, b
        varDec(node->child[0]);
        extDefList(node->child[2]);
    }
}

void specifier(ASTNode *node) {
    if (strcmp(node->child[0]->type, "TYPE")) {
        // TYPE: int, float, char
        
    } else {
        // StructSpecifier

    }
}

void structSpecifier(ASTNode *node) {
    if (node->child_count == 5) {
        // STRUCT ID LC DefList RC: struct node { int a; }

    } else {
        // STRUCT ID: struct node
        
    }
}

void varDec(ASTNode *node) {
    if (node->child_count == 1) {
        // ID: a
        
    } else {
        // VarDec LB INT RB: a[5][4]

    }
}

void funDec(ASTNode *node) {
    if (node->child_count == 4) {
        // ID LP VarList RP: int main(char arg, int num)

    } else {
        // ID LP RP: int main()

    }
}

void varList(ASTNode *node) {
    if (node->child_count == 3) {
        // ParamDec COMMA VarList: int a, int b

    } else {
        // ParamDec

    }
}

void paramDec(ASTNode *node) {
    // Specifier VarDec

}

void compSt(ASTNode *node) {
    // LC DefList StmtList RC: { def stmt }
    
}

void stmtList(ASTNode *node) {
    if (node->child_count == 2) {
        // Stmt StmtList

    }
}

void stmt(ASTNode *node) {
    if (node->child_count == 1) {
        // CompSt
        
    } else if (node->child_count == 2) {
        // Exp SEMI

    } else if (node->child_count == 3) {
        // RETURN Exp SEMI

    } else if (node->child_count == 5) {
        if (strcmp(node->child[0]->type, "IF") == 0) {
            // IF LP Exp RP Stmt

        } else {
            // WHILE LP Exp RP Stmt

        }
    } else if (node->child_count == 7) {
        // IF LP Exp RP Stmt ELSE Stmt


    } else if (node->child_count == 8) {
        // FOR LP Def Exp SEMI Exp RP Stmt

    }
}

void defList(ASTNode *node) {
    if (node->child_count == 2) {
        // Def DefList

    }
}

void def(ASTNode *node) {
    // Specifier DecList SEMI

}

void decList(ASTNode *node) {
    if (node->child_count == 1) {
        // Dec

    } else {
        // Dec COMMA DecList

    }
}

void dec(ASTNode *node) {
    if (node->child_count == 1) {
        // VarDec

    } else {
        // VarDec ASSIGN Exp

    }
}

void exp(ASTNode *node) {
    if (node->child_count >= 2) {
        switch(node->child[1]->type) {
            case "ASSIGN":
                break;
            case "AND":
                break;
            case "OR":
                break;
            case "LT":
                break;
            case "LE":
                break;
            case "GT":
                break;
            case "GE":
                break;
            case "NE":
                break;
            case "EQ":
                break;
            case "PLUS":
                break;
            case "MINUS":
                break;
            case "MUL":
                break;
            case "DIV":
                break;
            case "UNKNOW":
                break;
            case "EXP":
                if (strcmp(node->child[0]->type, "LP") == 0) {
                    // LP Exp RP: ()

                } else if (strcmp(node->child[0]->type, "MINUS") == 0) {
                    // MINUS Exp

                } else {
                    // NOT Exp

                }
                break;
            case "LP":
                if (node->child_count == 4) {
                    // ID LP Args RP

                } else {
                    // ID LP RP

                }
                break;
            case "LB":
                // Exp LB Exp RB

                break;
            case "NOT":
                // Exp DOT ID
                
                break;
        }
    } else if (node->child_count == 1) {
        switch(node->child[0]->type) {
            case "ID":
                break;
            case "INT":
                break;
            case "FLOAT":
                break;
            case "CHAR":
                break;
        }
    }
}

void args(ASTNode *node) {
    if (node->child_count == 1) {
        // Exp

    } else {
        // Exp COMMA Args

    }
}
