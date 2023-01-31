#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

#define SYMBOL_LIT_INTE 1
#define SYMBOL_LIT_CARA 2
#define SYMBOL_LIT_REAL 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 7

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

#endif

// END OF FILE