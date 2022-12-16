%{
  int yylex();
  void yyerror();
%}

%token KW_CARA
%token KW_INTE
%token KW_REAL

%token KW_SE
%token KW_ENTAUM
%token KW_SENAUM
%token KW_ENQUANTO
%token KW_ENTRADA
%token KW_ESCREVA
%token KW_RETORNE

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token TK_IDENTIFIER

%token LIT_INTEIRO
%token LIT_FLOAT
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '-' '+'
%left '/' '*'
%left '>' '<' '<=' '>=' '==' '!='
%left '&' '|' '~'
%right TK_IDENTIFIER '('


%%

program: cmd listCmd
         |
         ;

listCmd: cmd listCmd
         |
         ;

cmd:     TK_IDENTIFIER '=' expr ';'
         | TK_IDENTIFIER '[' expr ']' '=' expr ';'
         | KW_CARA TK_IDENTIFIER '=' expr ';'
         | KW_INTE TK_IDENTIFIER '=' expr ';'
         | KW_REAL TK_IDENTIFIER '=' expr ';'
         | KW_INTE TK_IDENTIFIER '[' index ']' array ';'
         | KW_CARA TK_IDENTIFIER '[' index ']' array ';'
         | KW_REAL TK_IDENTIFIER '[' index ']' array ';'

         | KW_CARA TK_IDENTIFIER '(' arrayParams ')' block
         | KW_INTE TK_IDENTIFIER '(' arrayParams ')' block
         | KW_REAL TK_IDENTIFIER '(' arrayParams ')' block
         | KW_ESCREVA arrayPrint ';'
         | block
         ;

expr:    TK_IDENTIFIER
         | TK_IDENTIFIER '[' expr ']'
         | TK_IDENTIFIER '(' array ')'
         | LIT_CHAR
         | LIT_INTEIRO
         | LIT_FLOAT
         | expr '+' expr
         | expr '-' expr
         | expr '*' expr
         | expr '/' expr
         | expr '<' expr
         | expr '>' expr
         | expr '<=' expr
         | expr '>=' expr
         | expr '==' expr
         | expr '!=' expr
         | expr '&' expr
         | expr '|' expr
         | expr '~' expr
         | '(' expr ')'
         | KW_ENTRADA
         ;

index:   LIT_INTEIRO
         | TK_IDENTIFIER
         ;

array:   expr array
         |
         ;

param:   KW_CARA TK_IDENTIFIER
         | KW_INTE TK_IDENTIFIER
         | KW_REAL TK_IDENTIFIER
         ;

arrayParams: param arrayParams
             |
             ;

arrayPrint:  LIT_STRING arrayPrint
             | expr arrayPrint
             |
             ;

block:       '{' listCmd '}'
             ;
%%

void yyerror() {
    fprintf(stderr, "Opps. Syntax error in line %d!\n", lineNumber);
    exit(3);
}