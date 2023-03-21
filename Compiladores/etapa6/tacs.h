#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MOVE 4
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
#define TAC_IFZ 16
#define TAC_LABEL 17
#define TAC_JUMP 18
#define TAC_NEW_ARRAY 19
#define TAC_VAL_ARRAY 20
#define TAC_MOVE_ARRAY 21
#define TAC_ARRAY 22
#define TAC_BEGINFUN 23
#define TAC_ENDFUN 24
#define TAC_PARAMS_NEW_FUN 25
#define TAC_CALL_FUN 26
#define TAC_PARAM_CALL 27
#define TAC_RET 28
#define TAC_PRINT 29
#define TAC_READ 30
#define TAC_VAR_DEC 31
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

// ASM GENERATION

TAC* tacReverse(TAC* tac);
void makeBinAsmOperation(FILE *fout, TAC *tac, char *op);
void makeBinAsmBoolOperation(FILE *fout, TAC *tac, char *op);
void generateAsm(TAC* first);
void printAsm(FILE *fout, TAC *tac);

#endif