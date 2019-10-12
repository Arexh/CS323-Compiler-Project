%{
    #include"lex.yy.c"
    void yyerror(const char*);
    int result;
%}
%error-verbose
%token INT
%token ADD SUB MUL DIV PERC EQ
%%
Final: Exp EQ { result = $1; }
Exp: Factor
    | Exp ADD Factor { $$ = $1 + $3; }
    | Exp SUB Factor { $$ = $1 - $3; }
    | Exp ADD INT PERC { $$ = $1 + $1 * $3 * 0.01; }
    | Exp SUB INT PERC { $$ = $1 - $1 * $3 * 0.01; }
    ;
Factor: INT
    | Factor MUL INT { $$ = $1 * $3; }
    | Factor DIV INT { $$ = $1 / $3; }
    ;
%%
void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}
#ifndef CALC_MAIN
#else
int main(){
    yyparse();
    printf(" = %d\n", result);
}
#endif


int evaluate(char *expr){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(expr);
    yyparse();
    yy_delete_buffer(buf);
    return result;
}

