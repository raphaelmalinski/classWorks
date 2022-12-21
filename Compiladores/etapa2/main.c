int yyparse();

int main(int argc, char** argv) {
  int tok;

   if (argc < 2) {
    fprintf(stderr, "Call : etapa2 filename\n");
    exit(1);
  }
  
  if(0 == (yyin = fopen(argv[1], "r"))) {
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    exit(2);
  }

  initMe();

  yyparse();
  
  printf("SUPER SUCCESS!!! This is a program! \nFile had %d lines\n", lineNumber);
  hashPrint();
  exit(0);
}
