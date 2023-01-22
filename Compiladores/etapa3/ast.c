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

typedef struct ast_node {
    int type;
    HASH * symbol;
    struct ast_node* son[MAX_SONS];
} AST;

AST * astCreate(int type, HASH * symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(AST* node, int level);


AST * astCreate(int type, HASH * symbol, AST* son0, AST* son1, AST* son2, AST* son3) {
    AST* newnode;
    newnode = (AST*) calloc(1, sizeof (AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = son0;
    newnode->son[1] = son1;
    newnode->son[2] = son2;
    newnode->son[3] = son3;
    return newnode;
}

void astPrint(AST* node, int level) {
    if(!node) return;

    int i;

    for (i = 0; i < level; ++i)
        fprintf(stderr, "  ");
    
    fprintf(stderr, "AST(");
    switch (node->type) {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break;
        case AST_MUL: fprintf(stderr, "AST_MUL"); break;
        case AST_DIV: fprintf(stderr, "AST_DIV"); break;
        case AST_LESS: fprintf(stderr, "AST_LESS"); break;
        case AST_GREATER: fprintf(stderr, "AST_GREATER"); break;
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_DIF: fprintf(stderr, "AST_DIF"); break;
        case AST_GE: fprintf(stderr, "AST_GE"); break;
        case AST_LE: fprintf(stderr, "AST_LE"); break;
        case AST_AND: fprintf(stderr, "AST_AND"); break;
        case AST_OR: fprintf(stderr, "AST_OR"); break;
        case AST_NOT: fprintf(stderr, "AST_NOT"); break;
        case AST_ENTRADA: fprintf(stderr, "AST_ENTRADA"); break;
        case AST_ARRAY: fprintf(stderr, "AST_ARRAY"); break;
        case AST_ATTR: fprintf(stderr, "AST_ATTR"); break;
        case AST_LIST_CMD: fprintf(stderr, "AST_LIST_CMD"); break;
        case AST_ARRAY_PRINT: fprintf(stderr, "AST_ARRAY_PRINT"); break;
        case AST_ARRAY_PARAMS: fprintf(stderr, "AST_ARRAY_PARAMS"); break;
        case AST_KW_CARA: fprintf(stderr, "AST_KW_CARA"); break;
        case AST_KW_INTE: fprintf(stderr, "AST_KW_INTE"); break;
        case AST_KW_REAL: fprintf(stderr, "AST_KW_REAL"); break;
        case AST_ATTR_ARRAY: fprintf(stderr, "AST_ATTR_ARRAY"); break;
        case AST_ENQUANTO: fprintf(stderr, "AST_ENQUANTO"); break;
        case AST_SE: fprintf(stderr, "AST_SE"); break;
        case AST_SE_SENAO: fprintf(stderr, "AST_SE_SENAO"); break;
        case AST_ESCREVA: fprintf(stderr, "AST_ESCREVA"); break;
        case AST_RETORNE: fprintf(stderr, "AST_RETORNE"); break;
        case AST_FUNCTION_CARA: fprintf(stderr, "AST_FUNCTION_CARA"); break;
        case AST_FUNCTION_INTE: fprintf(stderr, "AST_FUNCTION_INTE"); break;
        case AST_FUNCTION_REAL: fprintf(stderr, "AST_FUNCTION_REAL"); break;
        case AST_ATTR_CARA: fprintf(stderr, "AST_ATTR_CARA"); break;
        case AST_ATTR_INTE: fprintf(stderr, "AST_ATTR_INTE"); break;
        case AST_ATTR_REAL: fprintf(stderr, "AST_ATTR_REAL"); break;
        case AST_ATTR_ARRAY_INTE: fprintf(stderr, "AST_ATTR_ARRAY_INTE"); break;
        case AST_ATTR_ARRAY_CARA: fprintf(stderr, "AST_ATTR_ARRAY_CARA"); break;
        case AST_ATTR_ARRAY_REAL: fprintf(stderr, "AST_ATTR_ARRAY_REAL"); break;
        case AST_LIST_DECLARATIONS: fprintf(stderr, "AST_LIST_DECLARATIONS"); break;

        default: fprintf(stderr, "AST_UNKNOWN,\n"); break;
    }

    if(node->symbol != 0) {
        fprintf(stderr, ", %s)\n", node->symbol->text);
    }
    else {
        fprintf(stderr, ", 0)\n");
    }

    for(i=0; i < MAX_SONS; ++i) {
        astPrint(node->son[i], level+1);
    }
}