%{
    #include"syntax.tab.h"
    #include"ASTNode.c"
    #include"LinkedList.c"
    #include <string.h>
    #include <stdlib.h>
    /* library inclusions */ 
    int yycolno = 1; 
    int error = 0;
    #define YY_USER_ACTION \
        yylloc.first_line = yylineno; \
        yylloc.first_column = yycolno; \
        yylloc.last_line = yylineno; \
        yylloc.last_column = yycolno + yyleng; \
        yycolno += yyleng; \
    char *strCopy(char*);
    void record(char*);
    void appendLst(struct LstNode *);
    int wrong = 0;
    char *rec = "";
    struct LstHead *head = NULL;
    struct LstNode *node = NULL;
%}
letter [a-zA-Z]
number [0-9]
id_char [a-zA-Z0-9_]
id_char_first [a-zA-Z_]
ascii_hex_first [0-7]
hex [0-9a-fA-F]
not_hex [g-zG-Z"#$%&:?@\^`|~]
char [ !"#$%&'()*+,\-./0-9:;<=>?@A-Z[\]^_`a-z{|}~]
not_struct ["#$%&:?@\\^`|~]
struct [ .;,=<>!=+\-*/&|()\[\]{}]
struct_ne [.;,=<>!=+\-*/&|()\[\]{}]
%x COMMENT INT_HEX INT_BINARY_OR_WRONG_ID C_ID
%x DEFINE NAME TEXT
%%
"#define " {
        BEGIN(DEFINE);
        node = newLstNode();
    }
<DEFINE>{id_char_first}({id_char}|{struct_ne})* {
        printf("yytext: %s", yytext);
        node->name = strCopy(yytext);
        BEGIN(NAME);
    }
<DEFINE>[ \r\t] {}
<DEFINE>.{id_char}* { 
        fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        node = NULL;
        register int c;
        while((c = input()) != '\n' && c != EOF);
        if(c == '\n'){
            BEGIN(INITIAL);
            yylineno++;
        }else{
            fprintf(stderr, "Error at Line %d: EOF in macros\n", yylineno);
        }
    }
<NAME>.* { 
        node->text = strCopy(yytext);
        BEGIN(TEXT);
    }
<NAME>"\n" { 
        BEGIN(INITIAL);
        node->text = "";
        appendLst(node);
        printfLstNode(node);
        node = NULL;
        yylineno++; 
    }
<TEXT>"\n" {
        BEGIN(INITIAL);
        appendLst(node);
        printfLstNode(node);
        node = NULL;
        yylineno++; 
    }
"//".*"\n" {
        yylineno++; 
    }
"/*" { 
        BEGIN(COMMENT);
    }
<COMMENT>"*/" { 
        BEGIN(INITIAL); 
    }
<COMMENT>\n { 
        yylineno++; 
    }
<COMMENT>. {}
"0x" { 
        BEGIN(INT_HEX);
        record(yytext);
    }
<INT_HEX>{hex} {
        record(yytext);
    }
<INT_HEX>({struct}|"\n") { 
        if(yytext == "\n"){
            yylineno++;
        }
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
        }
        yylval.node = newLeaf("INT", strCopy(rec));
        wrong = 0;
        BEGIN(INITIAL);
        yyless(yyleng - 1);
        rec = "";
        return INT;
    }
<INT_HEX>. { 
        record(yytext);
        wrong = 1; 
    }
{number} { 
        BEGIN(INT_BINARY_OR_WRONG_ID); 
        record(yytext);
    }
<INT_BINARY_OR_WRONG_ID>({struct}|"\n") {
        if(yytext == "\n"){
            yylineno++;
        }
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
            yylval.node = newLeaf("ID", strCopy(rec));
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return ID;
        }else{
            yylval.node = newLeaf("INT", strCopy(rec));
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return INT;
        }
    }
<INT_BINARY_OR_WRONG_ID>{number} {
        record(yytext);
    }
<INT_BINARY_OR_WRONG_ID>. {
        wrong = 1;
        record(yytext);
    }
{number}*"."{number}+ { 
        yylval.node = newLeaf("FLOAT", strCopy(yytext)); 
        return FLOAT; 
    }
    /*Hex appears more than three times*/
"'\\x"({hex}|{not_hex}){2}({hex}|{not_hex})+"'" {
        yylval.node = newLeaf("CHAR", strCopy(yytext));
        fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        return CHAR;
    }
    /*Invalid hex lenth 2 or 1*/
"'\\x"(({hex}{not_hex})|({not_hex}{hex})|{not_hex})"'" {
        yylval.node = newLeaf("CHAR", strCopy(yytext));
        fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        return CHAR;
    }
"'"({char}|"\\x"{hex}{2})+"'" { 
        yylval.node = newLeaf("CHAR", strCopy(yytext));
        return CHAR; 
    }
"int"|"float"|"char" {         
        yylval.node = newLeaf("TYPE", strCopy(yytext)); 
        return TYPE; 
    }
"struct" {
        yylval.node = newNotation("STRUCT"); 
        return STRUCT; 
    }
"if" { 
        yylval.node = newNotation("IF"); 
        return IF; 
    }
"else" { 
        yylval.node = newNotation("ELSE"); 
        return ELSE; 
    }
"while" { 
        yylval.node = newNotation("WHILE"); 
        return WHILE; 
    }
"return" {
        yylval.node = newNotation("RETURN"); 
        return RETURN; 
    }
{id_char_first} { 
        BEGIN(C_ID);
        wrong = 0;
        record(yytext);
    }
{not_struct} {
        BEGIN(C_ID);
        wrong = 1;
        record(yytext);
    }
<C_ID>({struct}|"\n") {
        if(yytext == "\n"){
            yylineno++;
        }
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
        }
        wrong = 0;
        yylval.node = newLeaf("ID", strCopy(rec));
        BEGIN(INITIAL);
        yyless(yyleng - 1);
        rec = "";
        return ID;
    }
<C_ID>{id_char} {
        record(yytext);
    }
<C_ID>. {
        record(yytext);
        wrong = 1;
    }
"." { 
        yylval.node = newNotation("DOT"); 
        return DOT;
    }
";" { 
        yylval.node = newNotation("SEMI");
        return SEMI;
    }
"," { 
        yylval.node = newNotation("COMMA"); 
        return COMMA;
    }
"=" { 
        yylval.node = newNotation("ASSIGN"); 
        return ASSIGN;
    }
"<" { 
        yylval.node = newNotation("LT"); 
        return LT;
    }
"<=" { 
        yylval.node = newNotation("LE"); 
        return LE;
    }
">" { 
        yylval.node = newNotation("GT"); 
        return GT;
    }
">=" { 
        yylval.node = newNotation("GE"); 
        return GE;
    }
"!=" { 
        yylval.node = newNotation("NE"); 
        return NE;
    }
"==" { 
        yylval.node = newNotation("EQ"); 
        return EQ;
    }
"+" { 
        yylval.node = newNotation("PLUS"); 
        return PLUS;
    }
"-" { 
        yylval.node = newNotation("MINUS"); 
        return MINUS; 
    }
"*" { 
        yylval.node = newNotation("MUL"); 
        return MUL;
    }
"/" { 
        yylval.node = newNotation("DIV");
        return DIV;
    }
"&&" { 
        yylval.node = newNotation("AND");
        return AND;
    }
"||" { 
        yylval.node = newNotation("OR"); 
        return OR; 
    }
"!" { 
        yylval.node = newNotation("NOT");
        return NOT;
    }
"(" { 
        yylval.node = newNotation("LP"); 
        return LP; 
    }
")" { 
        yylval.node = newNotation("RP");
        return RP; 
    }
"[" { 
        yylval.node = newNotation("LB");
        return LB; 
    }
"]" { 
        yylval.node = newNotation("RB");
        return RB; 
    }
"{" { 
        yylval.node = newNotation("LC");
        return LC; 
    }
"}" { 
        yylval.node = newNotation("RC");
        return RC; 
    }
"\n" { 
        yylineno++;
    }
[ \r\t] { 
    }
. {
        fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
    }
%%
char* strCopy(char* src)
{
    char *dest = malloc(sizeof(src));
    strcpy(dest, src);
    return dest;
}

void record(char* ipt) 
{
    char *str = malloc(strlen(rec) + strlen(ipt));
    strcpy(str, rec);
    strcat(str, ipt);
    rec = str;
}

void appendLst(LstNode *node)
{
    if(head == NULL){
        head = newLstHead();
    }
    appendNode(head, node);
}