%{
  #include "hash.h"
%}

%union {
  HASH *symbol;
}

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEIRO
%token<symbol> LIT_FLOAT
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%left '-' '+'
%left '/' '*'
%left '>' '<' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '&' '|' '~'
%right TK_IDENTIFIER '('


%%

program: cmd
         | cmd ';' listCmd
         | var listCmd
         | function listCmd
         |
         ;

listCmd: cmd
         | cmd ';' listCmd
         | var listCmd
         | function listCmd
         |
         ;
        
var:     KW_CARA TK_IDENTIFIER '=' expr ';'
         | KW_INTE TK_IDENTIFIER '=' expr ';'
         | KW_REAL TK_IDENTIFIER '=' expr ';'
         | KW_INTE TK_IDENTIFIER '[' index ']' array ';'
         | KW_CARA TK_IDENTIFIER '[' index ']' array ';'
         | KW_REAL TK_IDENTIFIER '[' index ']' array ';'
         ;

function: KW_CARA TK_IDENTIFIER '(' arrayParams ')' block
          | KW_INTE TK_IDENTIFIER '(' arrayParams ')' block
          | KW_REAL TK_IDENTIFIER '(' arrayParams ')' block

cmd:     TK_IDENTIFIER '=' expr
         | TK_IDENTIFIER '[' expr ']' '=' expr
         | cmd KW_ENQUANTO '(' expr ')'
         | KW_ENTAUM cmd KW_SE '(' expr ')'
         | KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')'
         | KW_ESCREVA arrayPrint
         | KW_RETORNE expr
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
         | expr OPERATOR_EQ expr
         | expr OPERATOR_DIF expr
         | expr OPERATOR_GE expr
         | expr OPERATOR_LE expr
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
    fprintf(stderr, "Opps. Syntax error on line %d!\n", lineNumber);
    exit(3);
}