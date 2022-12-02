%{
int lineNumber = 1;
int running = 1;

#define KW_INT 1
#define KW_FOR 2
#define LIT_OCTAL 3
#define TK_ID 4
#define TK_ERROR 6

#include "hash.c"

%}

%x COMMENT

%%

"int"  		{ return KW_INT; }
"for"  		{ return KW_FOR; }
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

