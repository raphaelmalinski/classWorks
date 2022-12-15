%{
  int lineNumber = 1;
  int running = 1;

  #include "y.tab.h"

  #include "hash.c"
  #include "y.tab.c"
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

