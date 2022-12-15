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

%%

program: cmd tail
         |
         ;

tail:    cmd tail
         |
         ;

cmd:     TK_IDENTIFIER '=' expr ';'
         | KW_CARA TK_IDENTIFIER '=' expr ';'
         | KW_INTE TK_IDENTIFIER '=' expr ';'
         | KW_REAL TK_IDENTIFIER '=' expr ';'
         ;

expr:    LIT_CHAR
         | LIT_INTEIRO
         | LIT_FLOAT
         ;

%%

void yyerror() {
    fprintf(stderr, "Opps. Syntax error in line %d!\n", lineNumber);
    exit(3);
}