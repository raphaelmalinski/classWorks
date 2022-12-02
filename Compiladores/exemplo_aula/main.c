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
  hashInit();
  
  while(running) {
    tok = yylex();

    if (!running)
      break;
    
    switch(tok) {
      case KW_INT: { printf("KW INT "); } break;
      case KW_FOR: { printf("KW FOR "); } break;
      case LIT_OCTAL: { printf("LITERAL OCTAL (%s) ", yytext); } break;
      case TK_ID: { printf("Nome (%s) ", yytext); } break;
      case TK_ERROR: { printf("LEX ERROR "); } break;
      default: { printf("Symbol %d(%c) ", tok, tok); } break;
    }
  }
  printf("File had %d lines\n", lineNumber);
  hashPrint();
  exit(0);
}
