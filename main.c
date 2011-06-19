#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bMapNode {
	char *key;
	char *val;
	struct bMapNode *left;
	struct bMapNode *right;
} bMap;

bMap *consBMap(char* k, char* v) {
	if(!k || !v) return NULL;
	bMap *bm = malloc(sizeof(bMap));
	if(bm) {
		bm->left = NULL; bm->right = NULL;
		bm->key = malloc(strlen(k) + 1);
		strcpy(bm->key, k);
		bm->val = malloc(strlen(v) + 1);
		strcpy(bm->val, v);
	}
	return bm;
}

void deconsBMap(bMap *bm) {
	if(!bm) return;
	deconsBMap(bm->left);
	deconsBMap(bm->right);
	free(bm->key);
	free(bm->val);
}

bMap *findNode(bMap *bm, char* k) {
	if(!bm || !k) return NULL;
	int cmp = strcmp(bm->key, k);
	if(!cmp)
		return bm;
	if(cmp < 0)
		return findNode(bm->left, k);
	return findNode(bm->right, k);
}

int main(int argc, char **argv) {
	bMap *bm = consBMap("a", ".-");
	printf("Hello, world!\n");

	bMap *n = findNode(bm, "a");
	if(!n)
		printf("Not found");
	else
		printf("Value of bm[\"a\"]: %s\n", n->val);

	deconsBMap(bm);
	return 0;
}
