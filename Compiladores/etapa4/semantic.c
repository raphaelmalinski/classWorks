#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int SemanticErrors = 0;

void checkAndSetDeclarations(AST *node) {
    if(!node) return;

    switch (node->type) {
        case AST_ATTR_CARA:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_CARA;
            break;
        case AST_FUNCTION_CARA:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: function %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
            node->symbol->type = SYMBOL_FUNCTION;
            break;
        case AST_ATTR_INTE:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_INTE;
            break;
        case AST_FUNCTION_INTE:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: function %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
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

// falta colocar cara aqui pq é compativel
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

void checkOperands(AST *node) {
    if(!node) return;

    switch (node->type) {
        case AST_ADD: // IF OPERANDS ARE *NOT* VALID
            if(!isNumber(node->son[0])) {
                fprintf(stderr, "Semantic ERROR: invalid left operand for ADD\n");
                ++SemanticErrors;
            }
            if(!isNumber(node->son[1])) {
                fprintf(stderr, "Semantic ERROR: invalid right operand for ADD\n");
                ++SemanticErrors;
            }
            break;
    }
    
    int i;

    for(i=0; i < MAX_SONS; ++i)
        checkOperands(node->son[i]);
}

int getSemanticErrors() {
    return SemanticErrors;
}