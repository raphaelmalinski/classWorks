#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2) {
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;

    return newtac;
}

void tacPrint(TAC* tac) {
    if(!tac) return;
    if(tac->type == TAC_SYMBOL) return; 

    fprintf(stderr, "TAC(");
    switch (tac->type) {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
        case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
        case TAC_LESS: fprintf(stderr, "TAC_LESS"); break;
        case TAC_GREATER: fprintf(stderr, "TAC_GREATER"); break;
        case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
        case TAC_GE: fprintf(stderr, "TAC_GE"); break;
        case TAC_LE: fprintf(stderr, "TAC_LE"); break;
        case TAC_AND: fprintf(stderr, "TAC_AND"); break;
        case TAC_OR: fprintf(stderr, "TAC_OR"); break;
        case TAC_NOT: fprintf(stderr, "TAC_NOT"); break;
        case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
        default: fprintf(stderr, "TAC_UNKNOWN"); break;
    }

    fprintf(stderr, ",%s", (tac->res) ? tac->res->text : "0");
    fprintf(stderr, ",%s", (tac->op1) ? tac->op1->text : "0");
    fprintf(stderr, ",%s", (tac->op2) ? tac->op2->text : "0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC* tac){
    if(!tac) return;
    else {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }
}

TAC* tacJoin(TAC* l1, TAC* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    TAC* point;

    for (point = l2; point->prev != 0; point = point->prev);

    point->prev = l1;

    return l2;
}

// CODE GENERATION

TAC* makeBinOperation(int op, TAC* code[MAX_SONS]) {
    return tacJoin(tacJoin(code[0], code[1]), tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0));
}

TAC* makeSe(TAC* code0, TAC* code1);

TAC* generateCode(AST *node){
    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];

    if (!node) return 0;

    // PROCESS CHILDREN
    for(i = 0; i < MAX_SONS; ++i) {
        code[i] = generateCode(node->son[i]);
    }

    // PROCESS THIS NODE
    switch (node->type) {
        case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
        case AST_ADD: result = makeBinOperation(TAC_ADD, code); break;
        case AST_SUB: result = makeBinOperation(TAC_SUB, code); break;
        case AST_MUL: result = makeBinOperation(TAC_MUL, code); break;
        case AST_DIV: result = makeBinOperation(TAC_DIV, code); break;
        case AST_LESS: result = makeBinOperation(TAC_LESS, code); break;
        case AST_GREATER: result = makeBinOperation(TAC_GREATER, code); break;
        case AST_EQ: result = makeBinOperation(TAC_EQ, code); break;
        case AST_DIF: result = makeBinOperation(TAC_DIF, code); break;
        case AST_GE: result = makeBinOperation(TAC_GE, code); break;
        case AST_LE: result = makeBinOperation(TAC_LE, code); break;
        case AST_AND: result = makeBinOperation(TAC_AND, code); break;
        case AST_OR: result = makeBinOperation(TAC_OR, code); break;
        case AST_NOT: result = tacJoin(code[0], tacCreate(TAC_NOT, makeTemp(), code[0] ? code[0]->res : 0, 0)); break;
        case AST_ATTR: result = tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[0] ? code[0]->res : 0, 0)); break;
        case AST_SE: result = makeSe(code[0], code[1]); break;
        default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
                 break;
    }

    return result;
}

TAC* makeSe(TAC* code0, TAC* code1) {
    TAC * jumptac = 0;
    TAC * labeltac = 0;
    HASH * newlabel = 0;

    newlabel = makeLabel();

    jumptac = tacCreate(TAC_IFZ, newlabel, code1 ? code1->res : 0, 0);
    jumptac->prev = code1;
    labeltac = tacCreate(TAC_LABEL, newlabel, 0, 0);
    labeltac->prev = code0;
    return tacJoin(jumptac, labeltac);
}