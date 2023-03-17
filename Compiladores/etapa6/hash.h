#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

#define SYMBOL_LIT_INTE 1
#define SYMBOL_LIT_CARA 2
#define SYMBOL_LIT_REAL 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_VARIABLE 5
#define SYMBOL_LABEL 6
#define SYMBOL_IDENTIFIER 7
#define SYMBOL_FUNCTION 8

typedef struct hash_node {
    int type;
    char *text;
    struct hash_node *next;
} HASH;

void initMe(void);
int hashAddress(char *text);
HASH * hashFind(char *text);
HASH *hashInsert(int type, char *text);
void hashPrint(void);
HASH* makeTemp(void);
HASH* makeLabel(void);

#endif

// END OF FILE