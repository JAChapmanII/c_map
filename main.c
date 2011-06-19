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

int main(int argc, char **argv) {
	bMap *bm = consBMap("a", ".-");
	printf("Hello, world!\n");

	return 0;
}
