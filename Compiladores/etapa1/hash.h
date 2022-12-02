#define HASH_SIZE 997

typedef struct hash_node {
  int type;
  char *text;
  struct hash_node *next;
} HASH;

HASH *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH *hashInsert(int type, char *text);
void hashPrint(void);
