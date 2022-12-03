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

[;()\[\]{}=+-*/<>&|~] { return yytext[0]; }

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

. 		  { return TK_ERROR; }

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

