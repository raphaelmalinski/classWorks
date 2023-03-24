#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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

void astPrint(AST* node, int level, char *functionName, char *newFunction, int iParam) {
    if(!node) return;

    int i;
    HASH *nodeFunction;

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
        case AST_BLOCK: fprintf(stderr, "AST_BLOCK"); break;
        case AST_FUNCTION: fprintf(stderr, "AST_FUNCTION"); break;
        case AST_EXPR_PARENTESES: fprintf(stderr, "AST_EXPR_PARENTESES"); break;
        case AST_SYMBOL_ARRAY: fprintf(stderr, "AST_SYMBOL_ARRAY"); break;
        default: fprintf(stderr, "AST_UNKNOWN,\n"); break;
    }

    if(node->symbol != 0) {
        if (node->type == AST_FUNCTION)
            functionName = node->symbol->text;

        if (node->type == AST_FUNCTION_INTE || node->type == AST_FUNCTION_CARA || node->type == AST_FUNCTION_REAL) {
            newFunction = node->symbol->text;
        }

        fprintf(stderr, ", %s)\n", node->symbol->text);
    }
    else if(node->type == AST_ARRAY && strcmp(functionName, "")) {
        node->symbol = hashFind(functionName);
        fprintf(stderr, ", %s)\n", node->symbol->text);
    }
    else {
        fprintf(stderr, ", 0)\n");
        
        if (node->type == AST_ARRAY_PARAMS) {
            nodeFunction = hashFind(newFunction);
            strcpy(nodeFunction->params[iParam++], node->son[0]->symbol->text);
        }
    }

    for(i=0; i < MAX_SONS; ++i) {
        astPrint(node->son[i], level+1, functionName, newFunction, iParam);
    }
}

void descompila(AST* node, FILE * output) {
    if(!node) return;

    int i;

    switch (node->type) {
        case AST_SYMBOL: fputs(node->symbol->text, output); break;
        case AST_ENTRADA: fputs("entrada", output); break;
        case AST_ATTR: fputs(node->symbol->text, output); fputs(" = ", output); break;
        case AST_ARRAY_PRINT: if(!node->son[0]) { fputs(node->symbol->text, output); } break;
        case AST_KW_INTE: fputs("inte ", output); fputs(node->symbol->text, output); break;
        case AST_KW_CARA: fputs("cara ", output); fputs(node->symbol->text, output); break;
        case AST_KW_REAL: fputs("real ", output); fputs(node->symbol->text, output); break;
        case AST_ATTR_ARRAY: fputs(node->symbol->text, output); fputs("[", output); break;
        case AST_ESCREVA: if(!node->son[0]) { fputs("escreva ", output); } break;
        case AST_FUNCTION_INTE: fputs("inte ", output); fputs(node->symbol->text, output); fputs("(", output); break;
        case AST_FUNCTION_CARA: fputs("cara ", output); fputs(node->symbol->text, output); fputs("(", output); break;
        case AST_FUNCTION_REAL: fputs("real ", output); fputs(node->symbol->text, output); fputs("(", output); break;
        case AST_ATTR_INTE: fputs("inte ", output); fputs(node->symbol->text, output); fputs(" = ", output); break;
        case AST_ATTR_CARA: fputs("cara ", output); fputs(node->symbol->text, output); fputs(" = ", output); break;
        case AST_ATTR_REAL: fputs("real ", output); fputs(node->symbol->text, output); fputs(" = ", output); break;
        case AST_SYMBOL_ARRAY: fputs(node->symbol->text, output); fputs("[", output); break;
        case AST_ATTR_ARRAY_INTE: fputs("inte ", output); fputs(node->symbol->text, output); fputs("[", output); break;
        case AST_ATTR_ARRAY_CARA: fputs("cara ", output); fputs(node->symbol->text, output); fputs("[", output); break;
        case AST_ATTR_ARRAY_REAL: fputs("real ", output); fputs(node->symbol->text, output); fputs("[", output); break;
        case AST_FUNCTION: fputs(node->symbol->text, output); fputs("(", output); if(!node->son[0]) { fputs(")", output); } break;
        case AST_LIST_DECLARATIONS: 
            if(node->son[0]->type == AST_FUNCTION_INTE || node->son[0]->type == AST_FUNCTION_CARA || node->son[0]->type == AST_FUNCTION_REAL) {
                descompila(node->son[0], output); fputs("\n", output);
            } 
            else { descompila(node->son[0], output); fputs(";\n", output); } break;
        default: break;
    }

    for(i=0; i < MAX_SONS; ++i) {
        if(node->son[i]) {
            switch (node->type) {
                case AST_ADD: descompila(node->son[i], output); fputs(" + ", output); descompila(node->son[++i], output); break;
                case AST_SUB: descompila(node->son[i], output); fputs(" - ", output); descompila(node->son[++i], output); break;
                case AST_MUL: descompila(node->son[i], output); fputs(" * ", output); descompila(node->son[++i], output); break;
                case AST_DIV: descompila(node->son[i], output); fputs(" / ", output); descompila(node->son[++i], output); break;
                case AST_LESS: descompila(node->son[i], output); fputs(" < ", output); descompila(node->son[++i], output); break;
                case AST_GREATER: descompila(node->son[i], output); fputs(" > ", output); descompila(node->son[++i], output); break;
                case AST_EQ: descompila(node->son[i], output); fputs(" == ", output); descompila(node->son[++i], output); break;
                case AST_DIF: descompila(node->son[i], output); fputs(" != ", output); descompila(node->son[++i], output); break;
                case AST_GE: descompila(node->son[i], output); fputs(" >= ", output); descompila(node->son[++i], output); break;
                case AST_LE: descompila(node->son[i], output); fputs(" <= ", output); descompila(node->son[++i], output); break;
                case AST_AND: descompila(node->son[i], output); fputs(" & ", output); descompila(node->son[++i], output); break;
                case AST_OR: descompila(node->son[i], output); fputs(" | ", output); descompila(node->son[++i], output); break;
                case AST_NOT: fputs(" ~ ", output); descompila(node->son[i], output); break;
                case AST_EXPR_PARENTESES: fputs("(", output); descompila(node->son[i], output); fputs(")", output); break;
                case AST_ATTR_ARRAY_INTE: descompila(node->son[i], output); fputs("] ", output); descompila(node->son[++i], output); break;
                case AST_ATTR_ARRAY_CARA: descompila(node->son[i], output); fputs("] ", output); descompila(node->son[++i], output); break;
                case AST_ATTR_ARRAY_REAL: descompila(node->son[i], output); fputs("] ", output); descompila(node->son[++i], output); break;
                case AST_ATTR_ARRAY: descompila(node->son[i], output); fputs("] = ", output); descompila(node->son[++i], output); break;
                case AST_ARRAY: descompila(node->son[i], output); fputs(" ", output); break;
                case AST_ARRAY_PARAMS: descompila(node->son[i], output); fputs(" ", output); break;
                case AST_SYMBOL_ARRAY: descompila(node->son[i], output); fputs("]", output); break;
                case AST_LIST_DECLARATIONS: descompila(node->son[++i], output); break;
                case AST_FUNCTION_INTE: 
                    if(node->son[i+1]) { descompila(node->son[i], output); fputs(")", output); descompila(node->son[++i], output); }
                    else { fputs(")", output); descompila(node->son[i], output); } break;
                case AST_FUNCTION_CARA: 
                    if(node->son[i+1]) { descompila(node->son[i], output); fputs(")", output); descompila(node->son[++i], output); }
                    else fputs(")", output); descompila(node->son[i], output); break;
                case AST_FUNCTION_REAL: 
                    if(node->son[i+1]) { descompila(node->son[i], output); fputs(")", output); descompila(node->son[++i], output); }
                    else fputs(")", output); descompila(node->son[i], output); break;
                case AST_FUNCTION: descompila(node->son[i], output); fputs(")", output); break;
                case AST_BLOCK: 
                    if(node->son[i]->type == AST_BLOCK) { descompila(node->son[i], output); }
                    else { fputs("{\n", output); descompila(node->son[i], output); fputs("\n}", output); } break;
                case AST_LIST_CMD: descompila(node->son[i], output); if(node->son[++i]) fputs(";\n", output); descompila(node->son[i], output); break;
                case AST_ESCREVA: fputs("escreva ", output); descompila(node->son[i], output); break;
                case AST_ARRAY_PRINT: 
                    if(node->son[i]->type == AST_ARRAY_PRINT) { 
                        if(node->symbol) { fputs(node->symbol->text, output); } fputs(" ", output); descompila(node->son[i], output); 
                    }
                    else { descompila(node->son[i], output); } break;
                case AST_RETORNE: fputs("retorne ", output); descompila(node->son[i], output); break;
                case AST_ENQUANTO: descompila(node->son[i], output); fputs(" enquanto(", output); 
                                   descompila(node->son[++i], output); fputs(")", output); break;
                case AST_SE: 
                    if(node->son[i]->type == AST_BLOCK || node->son[i+1]) {
                        fputs(" entaum ", output); descompila(node->son[i], output); fputs(" se(", output); 
                        descompila(node->son[++i], output); fputs(")", output);
                    }
                    else {
                        fputs(" entaum ", output); fputs(" se(", output);
                        descompila(node->son[i], output); fputs(")", output);
                    } break;
                case AST_SE_SENAO: fputs(" entaum ", output); descompila(node->son[i], output); fputs(" senaum ", output); 
                                   descompila(node->son[++i], output); fputs(" se(", output); 
                                   descompila(node->son[++i], output);  fputs(")", output); break;
                default: descompila(node->son[i], output); break;
            }
        }
    }
}
