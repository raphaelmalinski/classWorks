#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

#define SYMBOL_LIT_INTE 1
#define SYMBOL_LIT_CARA 2
#define SYMBOL_LIT_REAL 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_VARIABLE 5
#define SYMBOL_FUNCTION 6
#define SYMBOL_VECTOR 7
#define SYMBOL_IDENTIFIER 8

#define DATATYPE_INTE 1
#define DATATYPE_CARA 2
#define DATATYPE_REAL 3
#define DATATYPE_BOOL 4

typedef struct hash_node {
    int type;
    int datatype;
    char *text;
    struct hash_node *next;
} HASH;

void initMe(void);
int hashAddress(char *text);
HASH * hashFind(char *text);
HASH *hashInsert(int type, char *text);
void hashPrint(void);
int hashCheckUndeclared(void);

#endif

// END OF FILE