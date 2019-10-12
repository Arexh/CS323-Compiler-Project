%{
    #include"syntax.tab.h"
    #include"ASTNode.c"
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
    char* strCopy(char*);
    char *splice(char*, char*);
    int wrong = 0;
    char *record = "";
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
%x COMMENT INT_HEX INT_BINARY_OR_WRONG_ID C_ID
%%
"//".*"\n" { yylineno++; }
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>\n   { yylineno++; }
<COMMENT>.    {}
"0x" { 
        BEGIN(INT_HEX);
        record = splice(record, yytext);
    }
<INT_HEX>{hex} {
        record = splice(record, yytext);
    }
<INT_HEX>({struct}|"\n") { 
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, record);
            error = 1;
        }
        yylval.node = newLeaf("INT", strCopy(record));
        wrong = 0;
        BEGIN(INITIAL);
        yyless(yyleng - 1);
        strcpy(record, "");
        return INT;
    }
<INT_HEX>. { 
        record = splice(record, yytext);
        wrong = 1; 
    }
{number} { 
        BEGIN(INT_BINARY_OR_WRONG_ID); 
        record = splice(record, yytext);
    }
<INT_BINARY_OR_WRONG_ID>({struct}|"\n") {
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, record);
            error = 1;
            yylval.node = newLeaf("ID", strCopy(record));
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            strcpy(record, "");
            return ID;
        }else{
            yylval.node = newLeaf("INT", strCopy(record));
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            strcpy(record, "");
            return INT;
        }
    }
<INT_BINARY_OR_WRONG_ID>{number} {
        record = splice(record, yytext);
    }
<INT_BINARY_OR_WRONG_ID>. {
        wrong = 1;
        record = splice(record, yytext);
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
        record = splice(record, yytext);
    }
{not_struct} {
        BEGIN(C_ID);
        wrong = 1;
        record = splice(record, yytext);
    }
<C_ID>({struct}|"\n") {
        if(wrong == 1){
            fprintf(stderr, "Error type A at Line %d: unknown lexeme %s\n", yylineno, record);
            error = 1;
        }
        wrong = 0;
        yylval.node = newLeaf("ID", strCopy(record));
        BEGIN(INITIAL);
        yyless(yyleng - 1);
        strcpy(record, "");
        return ID;
    }
<C_ID>{id_char} {
        record = splice(record, yytext);
    }
<C_ID>. {
        record = splice(record, yytext);
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
        yycolno = 1;
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

char *splice(char* first, char* second) {
    char *str = malloc(strlen(first) + strlen(second));
    strcpy(str, first);
    strcat(str, second);
    return str;
}