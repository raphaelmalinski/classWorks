#define HASH_SIZE 997

#define SYMBOL_LIT_INTE 1
#define SYMBOL_LIT_CARA 2
#define SYMBOL_IDENTIFIER 7

typedef struct hash_node {
    int type;
    char *text;
    struct hash_node *next;
} HASH;

HASH *Table[HASH_SIZE];

void initMe(void);
int hashAddress(char *text);
HASH * hashFind(char *text);
HASH *hashInsert(int type, char *text);
void hashPrint(void);