#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

void checkAndPrintAlreadyDeclaredError(HASH *symbol);
void checkAndPrintOperandsError(AST *node, char *operation);
void checkAndSetDeclarations(AST *node);
void checkUndeclared();
int isNumber(AST *son);
int isReal(AST *son);
void checkOperands(AST *node);
int getSemanticErrors();

#endif

// END OF FILE