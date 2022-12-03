int main(int argc, char** argv) {
  int tok;
  
  // if (argc < 2) {
  //   fprintf(stderr, "Call : etapa1 filename\n");
  //   exit(1);
  // }
  
  // if(0 == (yyin = fopen(argv[1], "r"))) {
  //  fprintf(stderr, "Cannot open file %s\n", argv[1]);
  //  exit(2);
  // }
  initMe();
  
  while(isRunning()) {
    tok = yylex();

    if (!isRunning())
      break;
    
    switch(tok) {
      case KW_CARA:     { printf("KW CARA "); } break;
      case KW_INTE:     { printf("KW INTE "); } break;
      case KW_REAL:     { printf("KW REAL "); } break;
      case KW_SE:       { printf("KW SE "); } break;
      case KW_ENTAUM:   { printf("KW ENTAUM "); } break;
      case KW_SENAUM:   { printf("KW SENAUM "); } break;
      case KW_ENQUANTO: { printf("KW ENQUANTO "); } break;
      case KW_ENTRADA:  { printf("KW ENTRADA "); } break;
      case KW_ESCREVA:  { printf("KW ESCREVA "); } break;
      case KW_RETORNE:  { printf("KW RETORNE "); } break;
      // case LIT_OCTAL: { printf("LITERAL OCTAL (%s) ", yytext); } break;
      // case TK_ID: { printf("Nome (%s) ", yytext); } break;
      // case TK_ERROR: { printf("LEX ERROR "); } break;
      default: { printf("Symbol %d(%c) ", tok, tok); } break;
    }
  }
  printf("File had %d lines\n", getLineNumber());
  hashPrint();
  exit(0);
}
