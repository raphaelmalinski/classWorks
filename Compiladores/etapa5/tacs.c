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
        case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
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
        case AST_ADD: result = tacJoin(tacJoin(code[0], code[1]), 
                               tacCreate(TAC_ADD, makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0)); break;
        case AST_ATTR: result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0] ? code[0]->res : 0, 0)); break;
        default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
                 break;
    }

    return result;
}