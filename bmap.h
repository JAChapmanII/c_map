#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bMapNode
{
	char *key;
	char *val;
	struct bMapNode *left;
	struct bMapNode *right;
} bMap;

typedef struct {
	char *k, *v;
} entry;

bMap *consBMap(char *k, char *v);
void deconsBMap(bMap *bm);

bMap *addNode(bMap *bm, char *k, char *v);
bMap *addNodes(bMap *bm, entry nodes[]);

bMap *rightRotation(bMap *n);
bMap *leftRotation(bMap *n);

bMap *findNode(bMap *bm, char *k);

int bMapDepth(bMap *bm);
int bMapSize(bMap *bm);

