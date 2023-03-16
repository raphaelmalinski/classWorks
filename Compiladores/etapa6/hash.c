#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

extern HASH *Table[HASH_SIZE];

void initMe(void) {
  int i = 0;

  for(i = 0; i < HASH_SIZE; ++i)
    Table[i] = 0;
}
    
int hashAddress(char *text) {
  int address = 1;
  int i = 0;
  for(i = 0; i < strlen(text); ++i)
    address = (address*text[i])%HASH_SIZE + 1;
  return address - 1;
}

HASH * hashFind(char *text) {
  int address;
  HASH*node;
  address = hashAddress(text);

  for (node=Table[address]; node; node=node->next)
    if (!strcmp(node->text, text))
      return node;

  return 0;
}
  
HASH *hashInsert(int type, char *text) {
  int address;
  HASH*node;
    
  if ((node = hashFind(text)) != 0)
    return node;

  address = hashAddress(text);
  node = (HASH*) calloc(1, sizeof(HASH));
  node->type = type;
  node->text = (char*) calloc(strlen(text) + 1, sizeof(char));
  strcpy(node->text, text);
  node->next = Table[address];
  Table[address] = node;
  return node;
}
  
void hashPrint(void) {
  int i = 0;
  HASH*node;

  for(i = 0; i < HASH_SIZE; ++i)
    for(node = Table[i]; node; node = node->next)
      printf("Table[%d] has %s - %d\n", i, node->text, node->type);
}

HASH* makeTemp(void) {
  static int serial = 0;
  char buffer[256] = "";

  sprintf(buffer, "mYWeeirT_emp%d", serial++);
  return hashInsert(SYMBOL_VARIABLE, buffer);
}


HASH* makeLabel(void) {
  static int serial = 0;
  char buffer[256] = "";

  sprintf(buffer, "mYLabule%d", serial++);
  return hashInsert(SYMBOL_LABEL, buffer);
}

void printAsm(FILE *fout) {
  int i = 0;
  int numString = 1;
  HASH*node;

  fprintf(fout, "## DATA SECTION\n"
	              "\t.section	.rodata\n\n");

  for(i = 0; i < HASH_SIZE; ++i)
    for(node = Table[i]; node; node = node->next) {
      if(node->type == SYMBOL_VARIABLE || node->type == SYMBOL_IDENTIFIER) {
        fprintf(fout, "_%s:\t.long\t0\n", node->text);
      } 
      else if(node->type == SYMBOL_LIT_INTE || node->type == SYMBOL_LIT_CARA || node->type == SYMBOL_LIT_REAL) {
        fprintf(fout, "_%s:\t.long\t%s\n", node->text, node->text);
      } 
      else if(node->type == SYMBOL_LIT_STRING) {
        fprintf(fout, "_myString%d:\n\t.string\t%s\n\t.text\n", numString++, node->text);
      }
    }
}