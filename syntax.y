%{
    #include"lex.yy.c"
    void yyerror(const char*);
    struct ASTNode *root;
    struct ASTNode *currentSpecifier;
    int structCheck;
    int structFather;
    void RPError(const int);
    void SEMIError(const int);
    void STRUCTError(const int, const char *);
    void DEFError(const int);
    void initial();
    #define MAX_LINE 1024
%}
%error-verbose
%union {
    struct ASTNode *node;
}
%token <node> INT FLOAT CHAR ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA FOR 
%token <node> ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC INCLUDE UNKNOW
%type  <node> Program ExtDefList ExtDef ExtDecList
%type  <node> Specifier StructSpecifier 
%type  <node> VarDec FunDec VarList ParamDec
%type  <node> CompSt StmtList Stmt DefList Def DecList Dec
%type  <node> Exp Args
%type  <node> FunID SpecifierTrigger STRUCTTrigger
%right ASSIGN
%left OR
%left AND
%left NE EQ GE GT LE LT
%left PLUS MINUS
%left MUL DIV
%right HIGH_MINUS NOT
%left LP RP LB RB DOT
%nonassoc LOWER_ELSE
%nonassoc ELSE
%nonassoc UNKNOW
%%
/* High-Level Definition */
Program: ExtDefList {
        $$ = newNode("Program", @$.first_line); 
        root = $$;
        appendChild($$, 1, $1); 
     };
ExtDefList: ExtDef ExtDefList {
    $$ = newNode("ExtDefList", @1.first_line); 
     appendChild($$, 2, $1, $2); 
    }
    | {
        $$ = newNode("NONE", @$.first_line);
    };
ExtDef: SpecifierTrigger ExtDecList SEMI {
        $$ = newNode("ExtDef", @$.first_line);
        appendChild($$, 3, $1, $2, $3);
    }
    | SpecifierTrigger ExtDecList error {
        SEMIError(@$.first_line);
    }
    | SpecifierTrigger SEMI {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 2, $1, $2);
        put_struct_specifier(currentSpecifier);
    }
    | SpecifierTrigger error {
        SEMIError(@$.first_line);
    }
    | SpecifierTrigger FunDec CompSt {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        // global function end
        function_stack_pop();
        hash_table_stack_pop();
        currentScopeNumber--;
    };
ExtDecList: VarDec {
        $$ = newNode("ExtDecList", @$.first_line); 
        appendChild($$, 1, $1);
        // put varDec
        put_var(currentSpecifier, $1);
    }
    | VarDec COMMA ExtDecList {
        $$ = newNode("ExtDecList", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        // put varDec
        put_var(currentSpecifier, $1);
    };

/* specifier */
Specifier: TYPE {
        $$ = newNode("Specifier", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | StructSpecifier {
        $$ = newNode("Specifier", @$.first_line); 
        appendChild($$, 1, $1);
    };
StructSpecifier: STRUCTTrigger ID LC DefList RC {
        $$ = newNode("StructSpecifier", @$.first_line); 
        appendChild($$, 5, $1, $2, $3, $4, $5);
        if (structFather) {
            structCheck = 1;
            structFather = 0;
        } else {
            structCheck = 0;
        }
    }
    | STRUCTTrigger ID {
        $$ = newNode("StructSpecifier", @$.first_line); 
        appendChild($$, 2, $1, $2);
        if (structFather) {
            structCheck = 1;
            structFather = 0;
        } else {
            structCheck = 0;
        }
    };
STRUCTTrigger: STRUCT {
        if (structCheck) {
            structFather = 1;
        } else {
            structCheck = 1;
        }
        $$ = $1;
    };
SpecifierTrigger: Specifier {
        currentSpecifier = $1->child[0];
        $$ = $1;
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
FunDec: FunID LP VarList RP {
        $$ = newNode("FunDec", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4);
    } 
    | FunID LP VarList error {
        RPError(@$.first_line);
    }
    | FunID LP RP {
        $$ = newNode("FunDec", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
    }
    | FunID LP error {
        RPError(@$.first_line);
    };
FunID: ID {
        $$ = newNode("FunID", @$.first_line);
        appendChild($$, 1, $1);
        // function start
        function_stack_push(currentSpecifier, $1->value, @$.first_line);
        currentScopeNumber++;
        hash_table_stack_push(currentFunction->hashTable);
    };
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
        put_para($1->child[0], $2);
    };

/* statement */
CompSt: LC DefList StmtList RC {
        $$ = newNode("CompSt", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4);
    }
    | LC error DefList StmtList RC {
        DEFError(@2.first_line);
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
    | IF LP Exp RP Stmt %prec LOWER_ELSE {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 5, $1, $2, $3, $4, $5);
    }
    | IF LP Exp error Stmt %prec LOWER_ELSE {
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
    | FOR LP Def Exp SEMI Exp RP Stmt {
        $$ = newNode("Stmt", @$.first_line); 
        appendChild($$, 8, $1, $2, $3, $4, $5, $6, $7, $8);
    }
    | FOR LP Def Exp error Exp RP Stmt {
        SEMIError(@$.first_line);
    }
    | FOR LP Def Exp error Exp error Stmt {
        SEMIError(@$.first_line);
        RPError(@$.first_line);
    }
    | FOR LP Def Exp SEMI Exp error Stmt {
        RPError(@$.first_line);
    }
    ;

/* local definition */
DefList: Def DefList {
        $$ = newNode("DefList", @$.first_line);
        appendChild($$, 2, $1, $2);
        if (strcmp($2->type, "NONE") == 0) {
            $$->value = malloc(sizeof(int));
            *(int *)$$->value = *(int*)$1->value + 0;
        } else {
            $$->value = malloc(sizeof(int));
            memcpy($$->value, $2->value, sizeof(int));
            *(int*)$$->value = *(int *)$$->value + *(int *)$1->value;
        }
    }
    | {
        $$ = newNode("NONE", @$.first_line);
    };
Def: SpecifierTrigger DecList SEMI {
        $$ = newNode("Def", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        $$->value = $2->value;
    }
    | SpecifierTrigger DecList error {
        SEMIError(@$.first_line);
    } 
    | SpecifierTrigger FunDec CompSt {
        $$ = newNode("ExtDef", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        // internal function end
        function_stack_pop();
        hash_table_stack_pop();
        currentScopeNumber--;
        $$->value = malloc(sizeof(int));
        *((int *)$$->value) = 1;
    };  
DecList: Dec {
        $$ = newNode("DecList", @$.first_line); 
        appendChild($$, 1, $1);
        $$->value = malloc(sizeof(int));
        *((int *)$$->value) = 1;
    }
    | Dec COMMA DecList {
        $$ = newNode("DecList", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        $$->value = malloc(sizeof(int));
        *((int *)$$->value) = *((int *)$3->value) + 1;
    }
    ;
Dec: VarDec {
        $$ = newNode("Dec", @$.first_line); 
        appendChild($$, 1, $1);
        if (structCheck == 0) {
            // put varDec
            puts("HERE");
            put_var(currentSpecifier, $1);
        }
    }
    | VarDec ASSIGN Exp {
        $$ = newNode("Dec", @$.first_line); 
        appendChild($$, 3, $1, $2, $3);
        if (structCheck == 0) {
            // put varDec
            put_var(currentSpecifier, $1);
            // assign check here
        }
    };

    /* Expression */
Exp:  Exp ASSIGN Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp AND Exp 
    { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp OR Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp LT Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp LE Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp GT Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp GE Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp NE Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp EQ Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp PLUS Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp MINUS Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp MUL Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp DIV Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp UNKNOW Exp {
        STRUCTError(@$.first_line, $2->value);
    }
    | LP Exp RP { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | LP Exp error {
        RPError(@$.first_line);
    }
    | MINUS Exp %prec HIGH_MINUS { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 2, $1, $2); 
    }
    | NOT Exp { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 2, $1, $2); 
    }
    | ID LP Args RP { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4); 
    }
    | ID LP Args error {
        RPError(@$.first_line);
    }
    | ID LP RP { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | ID LP error {
        RPError(@$.first_line);
    }
    | Exp LB Exp RB { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 4, $1, $2, $3, $4); 
    }
    | Exp DOT ID { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | ID { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 1, $1); 
    }
    | INT { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 1, $1); 
    }
    | FLOAT { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 1, $1);
    }
    | CHAR { 
        $$ = newNode("Exp", @$.first_line); 
        appendChild($$, 1, $1); 
    }
    | UNKNOW {

    }
    ;
Args: Exp COMMA Args  { 
        $$ = newNode("Args", @$.first_line); 
        appendChild($$, 3, $1, $2, $3); 
    }
    | Exp { 
        $$ = newNode("Args", @$.first_line); 
        appendChild($$, 1, $1); 
    }
    ;
%%
void RPError(const int lineno){
    fprintf(out, "Error type B at Line %d: Missing closing parenthesis ')'\n", lineno);
    error = 1;
}
void SEMIError(const int lineno){
    fprintf(out, "Error type B at Line %d: Missing semicolon ';'\n", lineno);
    error = 1;
}
void STRUCTError(const int lineno, const char *text){
    fprintf(out, "Error type B at Line %d: Unknow operator %s\n", lineno, text);
    error = 1;
}
void DEFError(const int lineno){
    fprintf(out, "Error type B at Line %d: Invalid Definition\n", lineno);
    error = 1;
}
void yyerror(const char *s){
    // fprintf(out, "%s", s);
}
void initial(){
    yycolno = 1;
    yylineno = 1;
    yytext = "";
    yyleng = 0;
    error = 0;
    wrong = 0;
    rec = "";
    head = NULL;
    node = NULL;
    neasted_start = 0;
    root = NULL;
    currentTable = new_hash_table();
    currentScopeNumber = 0;
    structCheck = 0;
    structFather = 0;
}
#ifndef CALC_MAIN
#else
int main(int count, char **args){
    if (count == 1){
        initial();
        out = stdout;
        yyparse();
        if (error == 0) {
            dfsPrintf(root, 0);
        }
    } else {
        for(int x = 1; x < count; x++){
            initial();
            int length = strlen(args[x]);
            char *output = malloc(length + 1);
            strcpy(output, args[x]);
            output[length] = 0;
            output[length - 1] = 't';
            output[length - 2] = 'u';
            output[length - 3] = 'o';
            char buf[MAX_LINE];
            int len;
            if ((fp = fopen(args[x],"r")) == NULL)
            {
                perror("fail to read");
                exit (1) ;
            }
            out = fopen(output, "w");
            yyrestart(fp);
            yyparse();
            if (error == 0)
                dfsPrintf(root, 0);
            fclose(fp);
            fclose(out);
        }        
        return 0;
    }
    
}
#endif

int evaluate(char *expr){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(expr);
    yyparse();
    yy_delete_buffer(buf);
    return 0;
}
