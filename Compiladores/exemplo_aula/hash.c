#include "hash.h"

void hashInit(void) {
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
 
HASH *hashInsert(int type, char *text) {
   int address;
   HASH*node;
   
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

   char *text_printed[HASH_SIZE];
   int j, was_printed;

   for(i = 0; i < HASH_SIZE; ++i) {
     for(node = Table[i]; node; node = node->next) {
      j = 0;
      was_printed = 0;

      // se a lista de strings é vazia, então nenhuma palavra foi impressa ainda 
      if(!text_printed[j]) {
        printf("Table[%d] has %s\n", i, node->text);
        text_printed[j] = node->text;
        continue;
      } 

      // compara a palavra atual com o que já foi impresso
      while(text_printed[j]) {
        if(strcmp(node->text, text_printed[j]) == 0) {
          was_printed = 1;
          break;
        }

        j++;
      }

      if(was_printed)
        continue;

      // se verificou que não foi impresso ainda, imprime na tela
      printf("Table[%d] has %s\n", i, node->text);
      text_printed[j] = node->text;
     }
   }
 }
