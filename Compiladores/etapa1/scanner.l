%{
  #include "tokens.h"
  #define HASH_SIZE 997

  int lineNumber = 1;
  int running = 1;

  typedef struct hash_node {
    int type;
    char *text;
    struct hash_node *next;
  } HASH;

  HASH *Table[HASH_SIZE];

  void initMe(void);
  int hashAddress(char *text);
  HASH *hashInsert(int type, char *text);
  void hashPrint(void);

  int getLineNumber(void) {
    return lineNumber;
  }

  int isRunning(void) {
    return running;
  }

  void initMe(void) {
    int i = 0;

    for(i = 0; i < HASH_SIZE; ++i)
      Table[i] = 0;
  }
    
  int hashAddress(char *text) {
    int address = 1;
    int i = 0;
    for(i = 0; i < strlen(text); ++i)
      address = (address*text[i])%HASH_SIZE + 1;
    return address - 1;
  }

  HASH * hashFind(char *text) {
  int address;
  HASH*node;
  address = hashAddress(text);

  for (node=Table[address]; node; node=node->next)
    if (!strcmp(node->text, text))
      return node;

  return 0;
}
  
  HASH *hashInsert(int type, char *text) {
    int address;
    HASH*node;
    
    if ((node = hashFind(text)) != 0)
      return node;

    address = hashAddress(text);
    node = (HASH*) calloc(1, sizeof(HASH));
    node->type = type;
    node->text = (char*) calloc(strlen(text) + 1, sizeof(char));
    strcpy(node->text, text);
    node->next = Table[address];
    Table[address] = node;
    return node;
  }
  
  void hashPrint(void) {
    int i = 0;
    HASH*node;

    for(i = 0; i < HASH_SIZE; ++i)
      for(node = Table[i]; node; node = node->next)
        printf("Table[%d] has %s\n", i, node->text);
  }
%}

%x COMMENT

%%

"cara"  	 { return KW_CARA; }
"inte"  	 { return KW_INTE; }
"real"  	 { return KW_REAL; }
"se"  		 { return KW_SE; }
"entaum"   { return KW_ENTAUM; }
"senaum"   { return KW_SENAUM; }
"enquanto" { return KW_ENQUANTO; }
"entrada"  { return KW_ENTRADA; }
"escreva"  { return KW_ESCREVA; }
"retorne"  { return KW_RETORNE; }

[;()\[\]{}=+\-*/<>&|~] { return yytext[0]; }

"<=" { return OPERATOR_LE; }
">=" { return OPERATOR_GE; }
"==" { return OPERATOR_EQ; }
"!=" { return OPERATOR_DIF; }

[a-z_.][a-z0-9_.]*	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }

[0-9]+             { hashInsert(LIT_INTEIRO, yytext); return LIT_INTEIRO; }
[0-9]+"."[0-9]+    { hashInsert(LIT_FLOAT, yytext); return LIT_FLOAT; }
[']"\\n"[']        { hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
[']"\\t"[']        { hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
['].[']            { hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
\"([^\\\"]|\\.)*\" { hashInsert(LIT_STRING, yytext); return LIT_STRING; }

[ \t,]

"\n" 		{ ++lineNumber; }

"///" 	{ BEGIN(COMMENT); }
"//".*

. 		  { return TOKEN_ERROR; }

<COMMENT>"\n"     { ++lineNumber; }
<COMMENT>.
<COMMENT>"\\\\\\" { BEGIN(INITIAL); }

%%

#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}

