%{
int lineNumber = 1;
int running = 1;

int getLineNumber(void) {
  return lineNumber;
}

int isRunning(void) {
  return running;
}

#include "hash.c"

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

[0-7]+ 		{ return LIT_OCTAL; }
[a-zA-Z]+ 		{ hashInsert(0, yytext); return TK_ID; }
[-;()=\[\]{}+*/] { return yytext[0]; }
[ \t]
"\n" 		{ ++lineNumber; }
"///" 		{ BEGIN(COMMENT); }
"//".*
. 		{ return TK_ERROR; }

<COMMENT>"\n"     { ++lineNumber; }
<COMMENT>.
<COMMENT>"\\\\\\" { BEGIN(INITIAL); }

%%

#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}

