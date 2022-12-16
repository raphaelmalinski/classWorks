int yyparse();

int main(int argc, char** argv) {
  int tok;

  initMe();

  yyparse();
  
  printf("SUPER SUCCESS!!! This is a program! \nFile had %d lines\n", lineNumber);
  hashPrint();
  exit(0);
}
