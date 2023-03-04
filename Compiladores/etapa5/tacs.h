#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_COPY 4
#define TAC_MUL 5
#define TAC_DIV 6
#define TAC_LESS 7
#define TAC_GREATER 8
#define TAC_EQ 9
#define TAC_DIF 10
#define TAC_GE 11
#define TAC_LE 12
#define TAC_AND 13
#define TAC_OR 14
#define TAC_NOT 15

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

TAC* makeBinOperation(int op, TAC* code[MAX_SONS]);
TAC* generateCode(AST *node);

#endif