#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int SemanticErrors = 0;

void checkAndPrintAlreadyDeclaredError(HASH *symbol) {
    if(symbol && symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr, "Semantic ERROR: variable %s already declared\n", symbol->text);
        ++SemanticErrors;
    }
}

void checkAndPrintIncompatibleTypeError(AST *node) {
    if(node->son[0] && 
            (node->son[0]->type == AST_AND ||
             node->son[0]->type == AST_OR ||
             node->son[0]->type == AST_LESS ||
             node->son[0]->type == AST_GREATER ||
             node->son[0]->type == AST_LE ||
             node->son[0]->type == AST_GE ||
             node->son[0]->type == AST_EQ ||
             node->son[0]->type == AST_DIF ||
             node->son[0]->type == AST_GREATER ||
             node->son[0]->type == AST_NOT)) {
        fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
        ++SemanticErrors;
    }
}

void checkAndSetDeclarations(AST *node) {
    if(!node) return;

    switch (node->type) {
        case AST_ATTR_CARA:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            checkAndPrintIncompatibleTypeError(node);
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_CARA;
            break;
        case AST_FUNCTION_CARA:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            node->symbol->type = SYMBOL_FUNCTION;
            break;
        case AST_ATTR_INTE:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            checkAndPrintIncompatibleTypeError(node);
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_INTE;
            break;
        case AST_FUNCTION_INTE:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            node->symbol->type = SYMBOL_FUNCTION;
            break;
        case AST_ATTR_REAL:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            checkAndPrintIncompatibleTypeError(node);
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_REAL;
            break;
        case AST_FUNCTION_REAL:
            checkAndPrintAlreadyDeclaredError(node->symbol);
            node->symbol->type = SYMBOL_FUNCTION;
            break;
    }

    int i;
    for(i=0; i < MAX_SONS; ++i)
        checkAndSetDeclarations(node->son[i]);
}

void checkUndeclared() {
    SemanticErrors += hashCheckUndeclared();
}

int isNumber(AST *son) {
    return (son->type == AST_ADD ||
            son->type == AST_SUB ||
            son->type == AST_MUL ||
            son->type == AST_DIV || 
            (son->type == AST_SYMBOL &&
                ((son->symbol->type == SYMBOL_LIT_INTE || son->symbol->type == SYMBOL_LIT_CARA) ||
                (son->symbol->type == SYMBOL_VARIABLE &&
                    (son->symbol->datatype == DATATYPE_INTE || son->symbol->datatype == DATATYPE_CARA))) ||
            (son->type == AST_FUNCTION &&
                (son->symbol->datatype == DATATYPE_INTE || son->symbol->datatype == DATATYPE_CARA))));
}

int isReal(AST *son) {
    return (son->type == AST_ADD ||
            son->type == AST_SUB ||
            son->type == AST_MUL ||
            son->type == AST_DIV || 
            (son->type == AST_SYMBOL &&
                (son->symbol->type == SYMBOL_LIT_REAL ||
                (son->symbol->type == SYMBOL_VARIABLE &&
                    son->symbol->datatype == DATATYPE_REAL)) ||
            (son->type == AST_FUNCTION &&
                son->symbol->datatype == DATATYPE_REAL)));
}

void checkAndPrintOperandsError(AST *node, char *operation) {
    if(!isNumber(node->son[0]) && !isReal(node->son[0])) {
        fprintf(stderr, "Semantic ERROR: invalid left operand for %s\n", operation);
        ++SemanticErrors;
    }
    if(!isNumber(node->son[1]) && !isReal(node->son[1])) {
        fprintf(stderr, "Semantic ERROR: invalid right operand for %s\n", operation);
        ++SemanticErrors;
    }
}

int isBool(AST *son) {
    return (son->type == AST_AND ||
            son->type == AST_OR ||
            son->type == AST_LESS ||
            son->type == AST_GREATER ||
            son->type == AST_LE ||
            son->type == AST_GE || 
            son->type == AST_EQ || 
            son->type == AST_DIF || 
            son->type == AST_NOT || 
            (son->type == AST_SYMBOL &&
                ((son->symbol->type == SYMBOL_LIT_INTE || son->symbol->type == SYMBOL_LIT_CARA || son->symbol->type == SYMBOL_LIT_REAL) ||
                (son->symbol->type == SYMBOL_VARIABLE &&
                    (son->symbol->datatype == DATATYPE_INTE || son->symbol->datatype == DATATYPE_CARA || son->symbol->type == DATATYPE_REAL))) ||
            (son->type == AST_FUNCTION &&
                (son->symbol->datatype == DATATYPE_INTE || son->symbol->datatype == DATATYPE_CARA || son->symbol->type == DATATYPE_REAL))));
}


void checkAndPrintBoolError(AST *node, char *operation) {
    if(!isBool(node->son[0])) {
        fprintf(stderr, "Semantic ERROR: invalid left operand for %s\n", operation);
        ++SemanticErrors;
    }
    if(node->type != AST_NOT && !isBool(node->son[1])) {
        fprintf(stderr, "Semantic ERROR: invalid right operand for %s\n", operation);
        ++SemanticErrors;
    }
}

void checkOperands(AST *node) {
    if(!node) return;

    switch (node->type) {
        case AST_ADD: checkAndPrintOperandsError(node, "ADD"); break;
        case AST_SUB: checkAndPrintOperandsError(node, "SUB"); break;
        case AST_MUL: checkAndPrintOperandsError(node, "MUL"); break;
        case AST_DIV: checkAndPrintOperandsError(node, "DIV"); break;
        case AST_AND: checkAndPrintBoolError(node, "AND"); break;
        case AST_OR: checkAndPrintBoolError(node, "OR"); break;
        case AST_LESS: checkAndPrintBoolError(node, "LESS"); break;
        case AST_GREATER: checkAndPrintBoolError(node, "GREATER"); break;
        case AST_GE: checkAndPrintBoolError(node, "GE"); break;
        case AST_LE: checkAndPrintBoolError(node, "LE"); break;
        case AST_EQ: checkAndPrintBoolError(node, "EQ"); break;
        case AST_DIF: checkAndPrintBoolError(node, "DIF"); break;
        case AST_NOT: checkAndPrintBoolError(node, "NOT"); break;
    }
    
    int i;

    for(i=0; i < MAX_SONS; ++i)
        checkOperands(node->son[i]);
}

int getSemanticErrors() {
    return SemanticErrors;
}