#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

void checkAndSetDeclarations(AST *node);
void checkUndeclared();
void checkOperands(AST *node);
int getSemanticErrors();

#endif

// END OF FILE