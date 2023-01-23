%{
  #include "hash.h"
  #include "ast.h"

  int yylex();
  void yyerror();

  AST *astOutput;
%}

%union {
  HASH *symbol;
  AST *ast;
}

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

%type<ast> program
%type<ast> listCmd
%type<ast> listDeclarations
%type<ast> var
%type<ast> function
%type<ast> cmd
%type<ast> expr
%type<ast> index
%type<ast> array
%type<ast> param
%type<ast> arrayParams
%type<ast> arrayPrint
%type<ast> block

%left '-' '+'
%left '/' '*'
%left '>' '<' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '&' '|' '~'
%right TK_IDENTIFIER '('


%%

program: block              { astOutput = $1; astPrint($1, 0); $$ = $1; }
         | listDeclarations { astOutput = $1; astPrint($1, 0); $$ = $1; }
         ;

listCmd: cmd                { $$ = astCreate(AST_LIST_CMD, 0, $1, 0, 0, 0); }
         | cmd ';' listCmd  { $$ = astCreate(AST_LIST_CMD, 0, $1, $3, 0, 0); }
         ;

listDeclarations: var listDeclarations        { $$ = astCreate(AST_LIST_DECLARATIONS, 0, $1, $2, 0, 0); }
                  | function listDeclarations { $$ = astCreate(AST_LIST_DECLARATIONS, 0, $1, $2, 0, 0); }
                  |                           { $$ = 0; }
                  ;
        
var:     KW_CARA TK_IDENTIFIER '=' expr ';'               { $$ = astCreate(AST_ATTR_CARA, $2, $4, 0, 0, 0); }
         | KW_INTE TK_IDENTIFIER '=' expr ';'             { $$ = astCreate(AST_ATTR_INTE, $2, $4, 0, 0, 0); }
         | KW_REAL TK_IDENTIFIER '=' expr ';'             { $$ = astCreate(AST_ATTR_REAL, $2, $4, 0, 0, 0); }
         | KW_INTE TK_IDENTIFIER '[' index ']' array ';'  { $$ = astCreate(AST_ATTR_ARRAY_INTE, $2, $4, $6, 0, 0); }
         | KW_CARA TK_IDENTIFIER '[' index ']' array ';'  { $$ = astCreate(AST_ATTR_ARRAY_CARA, $2, $4, $6, 0, 0); }
         | KW_REAL TK_IDENTIFIER '[' index ']' array ';'  { $$ = astCreate(AST_ATTR_ARRAY_REAL, $2, $4, $6, 0, 0); }
         ;

function: KW_CARA TK_IDENTIFIER '(' arrayParams ')' block   { $$ = astCreate(AST_FUNCTION_CARA, $2, $4, $6, 0, 0); }
          | KW_INTE TK_IDENTIFIER '(' arrayParams ')' block { $$ = astCreate(AST_FUNCTION_INTE, $2, $4, $6, 0, 0); }
          | KW_REAL TK_IDENTIFIER '(' arrayParams ')' block { $$ = astCreate(AST_FUNCTION_REAL, $2, $4, $6, 0, 0); }

cmd:     TK_IDENTIFIER '=' expr                           { $$ = astCreate(AST_ATTR, $1, $3, 0, 0, 0); }
         | TK_IDENTIFIER '[' expr ']' '=' expr            { $$ = astCreate(AST_ATTR_ARRAY, $1, $3, $6, 0, 0); }
         | cmd KW_ENQUANTO '(' expr ')'                   { $$ = astCreate(AST_ENQUANTO, 0, $1, $4, 0, 0); }
         | KW_ENTAUM cmd KW_SE '(' expr ')'               { $$ = astCreate(AST_SE, 0, $2, $5, 0, 0); }
         | KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')' { $$ = astCreate(AST_SE_SENAO, 0, $2, $4, $7, 0); }
         | KW_ESCREVA arrayPrint                          { $$ = astCreate(AST_ESCREVA, 0, $2, 0, 0, 0); }
         | KW_RETORNE expr                                { $$ = astCreate(AST_RETORNE, 0, $2, 0, 0, 0); }
         | block                                          { $$ = astCreate(AST_BLOCK, 0, $1, 0, 0, 0); }
         |                                                { $$ = 0; }
         ;

expr:    TK_IDENTIFIER                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         | TK_IDENTIFIER '[' expr ']'   { $$ = astCreate(AST_SYMBOL_ARRAY, $1, $3, 0, 0, 0); }
         | TK_IDENTIFIER '(' array ')'  { $$ = astCreate(AST_FUNCTION, $1, $3, 0, 0, 0); }
         | LIT_CHAR                     { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         | LIT_INTEIRO                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         | LIT_FLOAT                    { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         | expr '+' expr                { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
         | expr '-' expr                { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
         | expr '*' expr                { $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0); }
         | expr '/' expr                { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
         | expr '<' expr                { $$ = astCreate(AST_LESS, 0, $1, $3, 0, 0); }
         | expr '>' expr                { $$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0); }
         | expr OPERATOR_EQ expr        { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
         | expr OPERATOR_DIF expr       { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
         | expr OPERATOR_GE expr        { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
         | expr OPERATOR_LE expr        { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
         | expr '&' expr                { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
         | expr '|' expr                { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
         | expr '~' expr                { $$ = astCreate(AST_NOT, 0, $1, $3, 0, 0); }
         | '(' expr ')'                 { $$ = astCreate(AST_EXPR_PARENTESES, 0, $2, 0, 0, 0); }
         | KW_ENTRADA                   { $$ = astCreate(AST_ENTRADA, 0, 0, 0, 0, 0); }
         ;

index:   LIT_INTEIRO                    { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         | TK_IDENTIFIER                { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
         ;

array:   expr array                     { $$ = astCreate(AST_ARRAY, 0, $1, $2, 0, 0); }
         |                              { $$ = 0; }
         ;

param:   KW_CARA TK_IDENTIFIER          { $$ = astCreate(AST_KW_CARA, $2, 0, 0, 0, 0); }
         | KW_INTE TK_IDENTIFIER        { $$ = astCreate(AST_KW_INTE, $2, 0, 0, 0, 0); }
         | KW_REAL TK_IDENTIFIER        { $$ = astCreate(AST_KW_REAL, $2, 0, 0, 0, 0); }
         ;

arrayParams: param arrayParams          { $$ = astCreate(AST_ARRAY_PARAMS, 0, $1, $2, 0, 0); }
             |                          { $$ = 0; }
             ;

arrayPrint:  LIT_STRING arrayPrint      { $$ = astCreate(AST_ARRAY_PRINT, $1, $2, 0, 0, 0); }
             | expr arrayPrint          { $$ = astCreate(AST_ARRAY_PRINT, 0, $1, $2, 0, 0); }
             |                          { $$ = 0; }
             ;

block:       '{' listCmd '}' { $$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0); }
             ;
%%

void yyerror() {
    fprintf(stderr, "Opps. Syntax error on line %d!\n", lineNumber);
    exit(3);
}