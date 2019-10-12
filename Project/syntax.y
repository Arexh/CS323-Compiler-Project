%{
    #include"lex.yy.c"
    void yyerror(const char*);
    struct ASTNode *root;
    void RPError(const int);
    void SEMIError(const int);
%}
%union {
    struct ASTNode *node;
}
%token <node> INT FLOAT CHAR ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA
%token <node> ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC
%type  <node> Program ExtDefList ExtDef ExtDecList
%type  <node> Specifier StructSpecifier
%type  <node> VarDec FunDec VarList ParamDec
%type  <node> CompSt StmtList Stmt DefList Def DecList Dec
%type  <node> Exp Args
%right ASSIGN
%left OR
%left AND
%left NE EQ GE GT LE LT
%left ADD SUB
%left MUL DIV
%right MINUS NOT
%left LP RP LB RB DOT
%%
/* High-Level Definition */
Program: ExtDefList {
    $$ = newNode("Program", @$.first_line); 
     root = $$;
     appendChild($$, 1, $1); 
     };
ExtDefList: ExtDef ExtDefList {
    $$ = newNode("ExtDefList", @$.first_line); 
     appendChild($$, 2, $1, $2); 
    }
    | {
        $$ = newNode("NONE", @$.first_line);
    };
ExtDef: Specifier ExtDecList SEMI {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | Specifier ExtDecList error {
        SEMIError(@$.first_line);
    }
    | Specifier SEMI {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 2, $1, $2);
    }
    | Specifier error {
        SEMIError(@$.first_line);
    }
    | Specifier FunDec CompSt {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    };
ExtDecList: VarDec {
        $$ = newNode("ExtDecList", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | VarDec COMMA ExtDecList {
        $$ = newNode("ExtDecList", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    };

/* specifier */
Specifier: TYPE {
        $$ = newNode("Specifier", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | StructSpecifier {
        $$ = newNode("Specifier", @$.first_line); 
        appendChild($$, 1, $1);
    }
StructSpecifier: STRUCT ID LC DefList RC {
        $$ = newNode("StructSpecifier", @$.first_line); 
        appendChild($$, 5, $1, $2, $3, $4, $5);
    }
    | STRUCT ID {
        $$ = newNode("StructSpecifier", @$.first_line); 
        appendChild($$, 2, $1, $2);
    };

/* declarator */
VarDec: ID {
        $$ = newNode("VarDec", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | VarDec LB INT RB {
        $$ = newNode("VarDec", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4);
    };
FunDec: ID LP VarList RP {
        $$ = newNode("FunDec", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4);
    } 
    | ID LP VarList error {
        RPError(@$.first_line);
    }
    | ID LP RP {
        $$ = newNode("FunDec", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | ID LP error {
        RPError(@$.first_line);
    }
    ;
VarList: ParamDec COMMA VarList {
        $$ = newNode("VarList", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | ParamDec {
        $$ = newNode("VarList", @$.first_line); 
        appendChild($$, 1, $1);
    };
ParamDec: Specifier VarDec {
        $$ = newNode("ParamDec", @$.first_line); 
        appendChild($$, 2, $1, $2);
    };

/* statement */
CompSt: LC DefList StmtList RC {
        $$ = newNode("CompSt", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4);
    };
StmtList: Stmt StmtList {
        $$ = newNode("StmtList", @$.first_line); 
        appendChild($$, 2, $1, $2);
    }
    | {
        $$ = newNode("NONE", @$.first_line);
    };
Stmt: Exp SEMI {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 2, $1, $2);
    } 
    | Exp error {
        SEMIError(@$.first_line);
    }
    | CompSt {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | RETURN Exp SEMI {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | RETURN Exp error {
        SEMIError(@$.first_line);
    }
    | IF LP Exp RP Stmt {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 5, $1, $2, $3, $4, $5);
    }
    | IF LP Exp error Stmt {
        RPError(@$.first_line);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | IF LP Exp error Stmt ELSE Stmt {
        RPError(@$.first_line);
    }
    | WHILE LP Exp RP Stmt {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 5, $1, $2, $3, $4, $5);
    }
    | WHILE LP Exp error Stmt {
        RPError(@$.first_line);
    }
    ;

/* local definition */
DefList: Def DefList {
        $$ = newNode("DefList", @$.first_line); 
        appendChild($$, 2, $1, $2);
    }
    | {
        $$ = newNode("NONE", @$.first_line);
    };
Def: Specifier DecList SEMI {
        $$ = newNode("Def", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | Specifier DecList error {
        SEMIError(@$.first_line);
    }
    ;
DecList: Dec {
        $$ = newNode("DecList", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | Dec COMMA DecList {
        $$ = newNode("DecList", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    ;
Dec: VarDec {
        $$ = newNode("Dec", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | VarDec ASSIGN Exp {
        $$ = newNode("Dec", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    };

/* Expression */
Exp:  Exp ASSIGN Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp AND Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp OR Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp LT Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp LE Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp GT Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp GE Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp NE Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp EQ Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp PLUS Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp MINUS Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp MUL Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp DIV Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | LP Exp RP { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | LP Exp error {
        RPError(@$.first_line);
    }
    | MINUS Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 2, $1, $2); }
    | NOT Exp { $$ = newNode("Exp", @$.first_line); appendChild($$, 2, $1, $2); }
    | ID LP Args RP { $$ = newNode("Exp", @$.first_line); appendChild($$, 4, $1, $2, $3, $4); }
    | ID LP Args error {
        RPError(@$.first_line);
    }
    | ID LP RP { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | ID LP error {
        RPError(@$.first_line);
    }
    | Exp LB Exp RB { $$ = newNode("Exp", @$.first_line); appendChild($$, 4, $1, $2, $3, $4); }
    | Exp DOT ID { $$ = newNode("Exp", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | ID { $$ = newNode("Exp", @$.first_line); appendChild($$, 1, $1); }
    | INT { $$ = newNode("Exp", @$.first_line); appendChild($$, 1, $1); }
    | FLOAT { $$ = newNode("Exp", @$.first_line); appendChild($$, 1, $1); }
    | CHAR { $$ = newNode("Exp", @$.first_line); appendChild($$, 1, $1); }
    ;
Args: Exp COMMA Args  { $$ = newNode("Args", @$.first_line); appendChild($$, 3, $1, $2, $3); }
    | Exp { $$ = newNode("Args", @$.first_line); appendChild($$, 1, $1); }
    ;
%%
void RPError(const int lineno){
    fprintf(stderr, "Error type B at Line %d: Missing closing parenthesis ')'\n", lineno);
    error = 1;
}
void SEMIError(const int lineno){
    fprintf(stderr, "Error type B at Line %d: Missing semicolon ';'\n", lineno);
    error = 1;
}
void yyerror(const char *s){
    return;
}
#ifndef CALC_MAIN
#else
int main(){
    yyparse();
    if(error == 0)
        dfsPrintf(root, 0);
    return 0;
}
#endif


int evaluate(char *expr){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(expr);
    yyparse();
    yy_delete_buffer(buf);
    return 0;
}
