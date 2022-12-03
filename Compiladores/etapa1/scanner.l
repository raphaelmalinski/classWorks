%{
  #include "tokens.h"
  #define HASH_SIZE 997

  int lineNumber = 0;
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
  
  HASH *hashInsert(int type, char *text) {
    int address;
    HASH*node;
    
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

    char *text_printed[HASH_SIZE];
    int j, was_printed;

    for(i = 0; i < HASH_SIZE; ++i) {
      for(node = Table[i]; node; node = node->next) {
        j = 0;
        was_printed = 0;

        // se a lista de strings é vazia, então nenhuma palavra foi impressa ainda 
        if(!text_printed[j]) {
          printf("Table[%d] has %s\n", i, node->text);
          text_printed[j] = node->text;
          continue;
        } 

        // compara a palavra atual com o que já foi impresso
        while(text_printed[j]) {
          if(strcmp(node->text, text_printed[j]) == 0) {
            was_printed = 1;
            break;
          }

          j++;
        }

        if(was_printed)
          continue;

        // se verificou que não foi impresso ainda, imprime na tela
        printf("Table[%d] has %s\n", i, node->text);
        text_printed[j] = node->text;
      }
    }
  }
%}

%x COMMENT
%x STRING

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

[a-z_.][a-z0-9_.]+	{ hashInsert(0, yytext); return TK_IDENTIFIER; }

[0-9]+           { return LIT_INTEIRO; }
[0-9]+"."[0-9]+] { return LIT_FLOAT; }
[']"\n"[']       { return LIT_CHAR; }
[']"\\n"[']      { return LIT_CHAR; }
[']"\t"[']       { return LIT_CHAR; }
[']"\\t"[']      { return LIT_CHAR; }
['].[']          { return LIT_CHAR; }
["].+["]      	 { BEGIN(STRING); }

[0-9][a-z0-9_.]+ { return TOKEN_ERROR; }

[ \t,]

"\n" 		{ ++lineNumber; }

"///" 	{ BEGIN(COMMENT); }
"//".*

. 		  { return TOKEN_ERROR; }

<COMMENT>"\n"     { ++lineNumber; }
<COMMENT>.
<COMMENT>"\\\\\\" { BEGIN(INITIAL); }

<STRING>"\n"     { ++lineNumber; }
<STRING>"\\n"
<STRING>"\\\""
<STRING>["] { return LIT_STRING; BEGIN(INITIAL); }
<STRING>.
%%

#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}

