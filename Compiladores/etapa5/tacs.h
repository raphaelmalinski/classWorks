#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_COPY 4

typedef struct tacNode {
    int type;
    HASH * res;
    HASH * op1;
    HASH * op2;
    struct tacNode* prev;
    struct tacNode* next;
} TAC;

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);

// CODE GENERATION

TAC* generateCode(AST *node);

#endif