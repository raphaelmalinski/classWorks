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
        case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
        case TAC_NEW_ARRAY: fprintf(stderr, "TAC_NEW_ARRAY"); break;
        case TAC_VAL_ARRAY: fprintf(stderr, "TAC_VAL_ARRAY"); break;
        case TAC_MOVE_ARRAY: fprintf(stderr, "TAC_MOVE_ARRAY"); break;
        case TAC_ARRAY: fprintf(stderr, "TAC_ARRAY"); break;
        case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN"); break;
        case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN"); break;
        case TAC_PARAMS_NEW_FUN: fprintf(stderr, "TAC_PARAMS_NEW_FUN"); break;
        case TAC_CALL_FUN: fprintf(stderr, "TAC_CALL_FUN"); break;
        case TAC_PARAM_CALL: fprintf(stderr, "TAC_PARAM_CALL"); break;
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

TAC* makeSe(TAC* code0, TAC* code1);
TAC* makeSeSenao(TAC* code0, TAC* code1, TAC* code2);

TAC* makeBinOperation(int op, TAC* code[MAX_SONS]) {
    return tacJoin(tacJoin(code[0], code[1]), tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0));
}

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
        case AST_ATTR:
        case AST_ATTR_CARA:
        case AST_ATTR_INTE:
        case AST_ATTR_REAL:
            result = tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[0] ? code[0]->res : 0, 0)); break;
        case AST_SE: result = makeSe(code[0], code[1]); break;
        case AST_SE_SENAO: result = makeSeSenao(code[0], code[1], code[2]); break;
        case AST_ATTR_ARRAY_INTE:
        case AST_ATTR_ARRAY_CARA:
        case AST_ATTR_ARRAY_REAL:
            result = tacJoin(tacCreate(TAC_NEW_ARRAY, node->symbol, code[0] ? code[0]->res : 0, 0), code[1]); break;
        case AST_ARRAY: result = tacJoin(tacCreate(TAC_VAL_ARRAY, code[0] ? code[0]->res : 0, 0, 0), code[1]); break;
        case AST_ATTR_ARRAY: 
            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_MOVE_ARRAY, node->symbol, code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0));
            break;
        case AST_SYMBOL_ARRAY: result = tacJoin(code[0], tacCreate(TAC_ARRAY, makeTemp(), node->symbol, code[0] ? code[0]->res : 0)); break;
        case AST_FUNCTION_INTE:
        case AST_FUNCTION_CARA:
        case AST_FUNCTION_REAL:
            result = tacJoin(
                        tacJoin(
                            tacJoin(
                                tacJoin(
                                    tacCreate(TAC_BEGINFUN, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, 0, 0),
                                    code[0]
                                ), code[1]
                            ), code[2]
                        ), tacCreate(TAC_ENDFUN, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, 0, 0)
                     );
            break;
        case AST_ARRAY_PARAMS: result = tacJoin(code[3], tacJoin(tacCreate(TAC_PARAMS_NEW_FUN, node->son[0]->symbol, 0, 0), code[1])); break;
        case AST_FUNCTION: result = tacJoin(tacCreate(TAC_CALL_FUN, makeTemp(), node->symbol, 0), code[0]); break;
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

TAC* makeSeSenao(TAC* code0, TAC* code1, TAC* code2) {
    TAC * jumpIfZtac = 0;
    TAC * jumptac = 0;
    TAC * labelIfZtac = 0;
    TAC * labelJumptac = 0;

    HASH * labelIfZ = 0;
    HASH * labelJump = 0;

    labelIfZ = makeLabel();
    labelJump = makeLabel();

    jumpIfZtac = tacCreate(TAC_IFZ, labelIfZ, code2 ? code2->res : 0, 0);
    jumpIfZtac->prev = code2;
    labelIfZtac = tacCreate(TAC_LABEL, labelIfZ, 0, 0);
    labelIfZtac->prev = jumptac;

    jumptac = tacCreate(TAC_JUMP, labelJump, 0, 0);
    jumptac->prev = code0;
    labelJumptac = tacCreate(TAC_LABEL, labelJump, 0, 0);
    labelJumptac->prev = code1;
    
    return tacJoin(jumpIfZtac, tacJoin(jumptac, tacJoin(labelIfZtac, labelJumptac)));
}