%{
    #include"syntax.tab.h"
    #include"LinkedList.c"
    #include"Attributes.c"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    /* library inclusions */ 
    int yycolno = 1; 
    int error = 0;
    int wrong = 0;
    char *rec = "";
    struct LstHead *head = NULL;
    struct LstNode *node = NULL;
    int neasted_start;
    #define YY_USER_ACTION \
        yylloc.first_line = yylineno; \
        yylloc.first_column = yycolno; \
        yylloc.last_line = yylineno; \
        yylloc.last_column = yycolno + yyleng; \
        yycolno += yyleng; \
    char *strCopy(char*);
    char *splice_char(char*, char);
    void record(char*);
    void record_char(char);
    void unputStr(char*);
    void appendLst(struct LstNode *);
    int eatLine();
    char *splice(char*, char*);
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
struct_define [.;,=<>!=+\-*/&|)\[\]{}]
%x COMMENT INT_HEX INT_BINARY_OR_WRONG_ID C_ID NEASTED_COMMENT
%x DEFINE NAME TEXT WHE_PARA NAME_EAT PARA INCLUDE_HEAD INCLUDE_FILE UNDEF
%%
"#undef" {
        BEGIN(UNDEF);
    }
<UNDEF>[ \r\t] {
    }
<UNDEF>"\n" {
        yylineno++;
        fprintf(out, "Error UNDEF at Line %d: empty macro\n", yylineno);
        eatLine();
    }
<UNDEF>[^ \r\t\n]* {
        char *name = strCopy(yytext);
        if (head == NULL || !checkName(head, name)){
            fprintf(out, "Error UNDEF at Line %d: not exist macro name\n", yylineno);
        } else {
            removeNode(head, name);
        }
        eatLine();
    }
"#define " {
        BEGIN(DEFINE);
        node = newLstNode();
    }
<DEFINE>{id_char_first}({id_char}|{struct_define})* {
        node->name = strCopy(yytext);
        node->name_len = yyleng;
        rec = "";
        BEGIN(NAME);
    }
<DEFINE>[ \r\t] {}
<DEFINE>"\n" {
        fprintf(out, "Error DEFINE at Line %d: empty macro\n", yylineno);
        yylineno++;
        BEGIN(INITIAL);
    }
<DEFINE>.{id_char}* { 
        fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        node = NULL;
        eatLine();
    }
<WHE_PARA>" " {}
<WHE_PARA>"," {
        fprintf(out, "Error macro at Line %d: empty parameter\n", yylineno);
        eatLine();
    }
<WHE_PARA>[^ ,)]* {
        if (checkArg(node->argHead, yytext)){
            fprintf(out, "Error macro at Line %d: duplicate parameter\n", yylineno);
            eatLine();
        } else {
            appendArgId(node->argHead, strCopy(yytext));
            BEGIN(PARA);
        }
    }
<PARA>" "*"," {
        BEGIN(WHE_PARA);
    }
<PARA>" "*")"";"" "* {
        node->semi = 1;
        BEGIN(NAME_EAT);
    }
<PARA>" "*")"" "* {
        BEGIN(NAME_EAT);
    }
<PARA>" " {
        fprintf(out, "Error at Line %d: missing right parenthesis\n", yylineno);
        eatLine();
    }
<NAME>"(" {
        record("(");
        BEGIN(WHE_PARA);
    }
<NAME>" " { 
        BEGIN(NAME_EAT);
    }
<NAME_EAT>[^ \n].* {
        node->text = strCopy(yytext);
        BEGIN(TEXT);
    }
<NAME_EAT>"\n" { 
        BEGIN(INITIAL);
        node->text = "";
        appendLst(node);
        node = NULL;
        yylineno++; 
    }
<TEXT>"\n" {
        BEGIN(INITIAL);
        appendLst(node);
        node = NULL;
        yylineno++; 
    }
"//".*"\n" {
        yylineno++; 
    }
"/*" { 
        rec = "";
        BEGIN(COMMENT);
    }
<COMMENT>"/*" {
        neasted_start = yylineno;
        BEGIN(NEASTED_COMMENT);
    }
<COMMENT>"*/" { 
        rec = "";
        BEGIN(INITIAL);
    }
<COMMENT>\n {
        yylineno++; 
    }
<COMMENT><<EOF>> {
        fprintf(out, "Error COMMENT at Line %d: missing '*/'\n", yylineno);
    }
<COMMENT>. {
    }
<NEASTED_COMMENT>"*/" {
        fprintf(out, "Error COMMENT from Line %d to Line %d: nested multi-line comments\n", neasted_start, yylineno);
        BEGIN(COMMENT);
    }
<NEASTED_COMMENT><<EOF>> {
        fprintf(out, "Error COMMENT at Line %d: missing '*/'\n", yylineno);
    }
<NEASTED_COMMENT>. {
    }
<NEASTED_COMMENT>\n {
        yylineno++;
    }
"0x" { 
        BEGIN(INT_HEX);
        rec = "";
        record(yytext);
    }
<INT_HEX>{hex} {
        record(yytext);
    }
<INT_HEX>({struct}|"\n") { 
        if (yytext == "\n"){
            yylineno++;
        }
        if (wrong == 1){
            fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
            yylval.node = newLeaf("INT", strCopy(rec));
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return UNKNOW;
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
        if (yytext == "\n"){
            yylineno++;
        }
        if (wrong == 1){
            fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
            yylval.node = newLeaf("ID", strCopy(rec));
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return ID;
        } else {
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
        fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        return UNKNOW;
    }
    /*Invalid hex lenth 2 or 1*/
"'\\x"(({hex}{not_hex})|({not_hex}{hex})|{not_hex})"'" {
        yylval.node = newLeaf("CHAR", strCopy(yytext));
        fprintf(out,  "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        return UNKNOW;
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
"for" {
        yylval.node = newNotation("FOR");
        return FOR;
    }
"break" {
        yylval.node = newNotation("BREAK");
        return BREAK;
    }
"continue" {
        yylval.node = newNotation("CONTINUE");
        return CONTINUE;
    }
{id_char_first} {
        rec = "";
        int judge = 1;
        int change = 0;
        if (head != NULL) {
            int i;
            LstNode *tmp = head->next;
            register int c = 0;
            for(i = 0; i < head->num; i++){
                if (yytext[0] == tmp->name[0]){
                    record(yytext);
                    change = 1;
                    int j;
                    for(j = 0; j < tmp->name_len - 1; j++){
                        c = input();
                        if (c != EOF){
                            record_char(c);
                        } else {
                            /* fail */
                            unputStr(rec);
                            rec = "";
                            break;
                        }
                    }
                    if (c == EOF){
                        /* fail */
                        continue;
                    }
                    if (!strcmp(tmp->name, rec)){
                        /* success */
                        if (tmp->argHead->num == 0){
                            unputStr(strCopy(tmp->text));
                            rec = "";
                            yytext = "";
                            judge = 0;
                            break;
                        } else {
                            char next_char = input();
                            record_char(next_char);
                            int state = 0;
                            int count = 0;
                            Arg *arg = tmp->argHead->next;
                            while(next_char != EOF){
                                if (state == 0){
                                    if (next_char == '('){
                                        state = 1;
                                    } else {
                                        unputStr(rec);
                                        break;
                                    }
                                } else if (state == 1){
                                    if (next_char == ','){
                                        if (arg->match == NULL){
                                            unputStr(rec);
                                            break;
                                        } else {
                                            if (arg->next != NULL){
                                                count++;
                                                arg = arg->next;
                                                state = 1;
                                            } else {
                                                unputStr(rec);
                                                break;
                                            }
                                        }
                                    } else if (next_char == ' '){
                                        state = 1;
                                    } else if (next_char == ')'){
                                        if (arg->match != NULL && count + 1 == tmp->argHead->num){
                                            if (tmp->semi){
                                                next_char = input();
                                                record_char(next_char);
                                                if (next_char == ';'){
                                                    /* success */
                                                    unputStr(replace(tmp->text, tmp->argHead));
                                                    clearMatch(tmp->argHead);
                                                    rec = "";
                                                    yytext = "";
                                                    judge = 0;
                                                    break;
                                                } else {
                                                    unputStr(rec);
                                                    break;
                                                }
                                            } else {
                                                /* success */
                                                unputStr(replace(arg->match, tmp->argHead));
                                                clearMatch(tmp->argHead);
                                                rec = "";
                                                yytext = "";
                                                judge = 0;
                                                break;
                                            }
                                        } else {
                                            unputStr(rec);
                                            break;
                                        }
                                    } else {
                                        arg->match = splice_char(arg->match, next_char);
                                        state = 1;
                                    }
                                }
                                next_char = input();
                                record_char(next_char);
                            }
                            if (next_char == EOF){
                                unputStr(rec);
                            }
                        }
                    } else {
                        /* fail */
                        unputStr(rec);
                        rec = "";
                    }
                }
                tmp = tmp->next;
            }
        }
        if (judge) {
            if (change){
                yytext = "";
                yytext = splice_char(yytext, input());
            }
            BEGIN(C_ID);
            wrong = 0;
            record(yytext);
        }
    }
<C_ID>({struct}|"\n") {
        if (yytext == "\n"){
            yylineno++;
        }
        if (wrong == 1){
            fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, rec);
            error = 1;
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return UNKNOW;
        } else {
            yylval.node = newLeaf("ID", strCopy(rec));
            wrong = 0;
            BEGIN(INITIAL);
            yyless(yyleng - 1);
            rec = "";
            return ID;
        }
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
"|" {
        fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        yylval.node = newLeaf("UNKNOW", "|");
        return UNKNOW; 
    }
"&" {
        fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
        yylval.node = newLeaf("UNKNOW", "&");
        return UNKNOW; 
    }
{not_struct} {
        BEGIN(C_ID);
        wrong = 1;
        rec = "";
        record(yytext);
    }
"\n" { 
        yylineno++;
    }
[ \r\t] { 
    }
. {
        fprintf(out, "Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
        error = 1;
    }
<<EOF>> {
        yyterminate();
    }
%%
char* strCopy(char* src)
{
    char *dest = malloc(strlen(src));
    strcpy(dest, src);
    return dest;
}

void record(char* ipt)
{
    char *str = malloc(strlen(rec) + strlen(ipt) + 1);
    strcpy(str, rec);
    strcat(str, ipt);
    str[strlen(rec) + strlen(ipt)] = 0;
    rec = str;
}

void appendLst(LstNode *node)
{
    if (head == NULL){
        head = newLstHead();
    }
    appendNode(head, node);
}

void record_char(char ipt)
{
    char *str = malloc(strlen(rec) + 2);
    strcpy(str, rec);
    str[strlen(rec)] = ipt;
    str[strlen(rec) + 1] = 0;
    rec = str;
}

void unputStr(char* str){
    int i = strlen(str) - 1;
    for (; i >= 0; i--){
        unput(str[i]);
    }
}

char *splice(char* a, char* b)
{
    char *str = malloc(strlen(a) + strlen(b) + 1);
    strcpy(str, a);
    strcat(str, b);
    str[strlen(a) + strlen(b)] = 0;
    return str;
}

int eatLine()
{
    register int c;
    while((c = input()) != '\n' && c != EOF);
    if (c == '\n'){
        BEGIN(INITIAL);
        yylineno++;
    } else {
        fprintf(out, "Error at Line %d: EOF in macros\n", yylineno);
        yyterminate();
    }
}

char *splice_char(char* a, char b)
{   
    char *str;
    if (a == NULL){
        str = malloc(2);
        str[0] = b;
        str[1] = 0;
    } else {
        str = malloc(strlen(a) + 2);
        strcpy(str, a);
        str[strlen(a)] = b;
        str[strlen(a) + 1] = 0;
    }
    return str;
}