#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MUL 4
#define AST_DIV 5
#define AST_LESS 6
#define AST_GREATER 7
#define AST_EQ 8
#define AST_DIF 9
#define AST_GE 10
#define AST_LE 11
#define AST_AND 12
#define AST_OR 13
#define AST_NOT 14
#define AST_ENTRADA 15
#define AST_ARRAY 16
#define AST_ATTR 17
#define AST_LIST_CMD 18
#define AST_ARRAY_PRINT 19
#define AST_ARRAY_PARAMS 20
#define AST_KW_CARA 21
#define AST_KW_INTE 22
#define AST_KW_REAL 23
#define AST_ATTR_ARRAY 24
#define AST_ENQUANTO 25
#define AST_SE 26
#define AST_SE_SENAO 27
#define AST_ESCREVA 28
#define AST_RETORNE 29
#define AST_FUNCTION_CARA 30
#define AST_FUNCTION_INTE 31
#define AST_FUNCTION_REAL 32
#define AST_ATTR_CARA 33
#define AST_ATTR_INTE 34
#define AST_ATTR_REAL 35
#define AST_ATTR_ARRAY_INTE 36
#define AST_ATTR_ARRAY_CARA 37
#define AST_ATTR_ARRAY_REAL 38
#define AST_LIST_DECLARATIONS 39
#define AST_BLOCK 40
#define AST_FUNCTION 41
#define AST_EXPR_PARENTESES 42
#define AST_SYMBOL_ARRAY 43

typedef struct ast_node {
    int type;
    HASH * symbol;
    struct ast_node* son[MAX_SONS];
} AST;

AST * astCreate(int type, HASH * symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(AST* node, int level, char *functionName, char *newFunction, int iParam);
void descompila(AST* node, FILE * output);

#endif

// END OF FILE