#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bMapNode {
	char *key;
	char *val;
	struct bMapNode *left;
	struct bMapNode *right;
} bMap;

bMap *consBMap(char *k, char *v) { //{{{
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
} //}}}

void deconsBMap(bMap *bm) { //{{{
	if(!bm) return;
	deconsBMap(bm->left);
	deconsBMap(bm->right);
	free(bm->key);
	free(bm->val);
} //}}}

bMap *findNode(bMap *bm, char *k) { //{{{
	if(!bm || !k) return NULL;
	int cmp = strcmp(bm->key, k);
	if(!cmp)
		return bm;
	if(cmp < 0)
		return findNode(bm->left, k);
	return findNode(bm->right, k);
} //}}}

bMap *rightRotation(bMap *n);
bMap *leftRotation(bMap *n);

bMap *addNode(bMap *bm, char *k, char *v) { //{{{
	if(!bm || !k || !v) return;
	int cmp = strcmp(bm->key, k);
	if(!cmp) {
		if(strcmp(bm->val, v)) {
			free(bm->val);
			bm->val = malloc(strlen(k) + 1);
			strcpy(bm->val, v);
		}
	}

	bMap **child;
	if(cmp < 0)
		child = &bm->left;
	else
		child = &bm->right;

	if(!*child)
		*child = consBMap(k, v);
	else
		*child = addNode(*child, k, v);

	int ld = bMapDepth(bm->left), rd = bMapDepth(bm->right);
	if(rd - ld > 1) {
		int r_ld = bMapDepth(bm->right->left), r_rd = bMapDepth(bm->right->right);
		if(r_ld > r_rd)
			bm->right = rightRotation(bm->right);
		bm = leftRotation(bm);
	} else if(ld - rd > 1) {
		int l_ld = bMapDepth(bm->left->left), l_rd = bMapDepth(bm->left->right);
		if(l_rd > l_ld)
			bm->left = leftRotation(bm->left);
		bm = rightRotation(bm);
	}

	return bm;
} //}}}

bMap *rightRotation(bMap *n) { //{{{
	bMap *nr = n->left, *c = n->left->right;

	nr->right = n;
	n->left = c;

	return nr;
} //}}}

bMap *leftRotation(bMap *n) { //{{{
	bMap *nr = n->right, *b = n->right->left;

	nr->left = n;
	n->right = b;

	return nr;
} //}}}

int bMapSize(bMap *bm) { //{{{
	if(!bm) return 0;
	return bMapSize(bm->left) + bMapSize(bm->right) + 1;
} //}}}

typedef struct {
	char *k, *v;
} entry;

bMap *addNodes(bMap *bm, entry nodes[]) {
	while(nodes->k)
		bm = addNode(bm, nodes->k, nodes->v), ++nodes;
	return bm;
}

int bMapDepth(bMap *bm) {
	if(!bm) return 0;
	int ld = bMapDepth(bm->left), rd = bMapDepth(bm->right);
	if(ld > rd)
		return ld + 1;
	else
		return rd + 1;
}

int main(int argc, char **argv) {
	bMap *bm = consBMap("m", "--"); 
	static entry characters[] = { 
		{"f", "..-."}, {"c", "-.-."}, {"a", ".-"}, {"b", "-..."}, {"d", "-.."},
		{"e", "."}, {"i", ".."}, {"g", "--."}, {"h", "...."}, {"j", ".---"},
		{"k", "-.-"}, {"l", ".-.."}, {"t", "-"}, {"p", ".--."}, {"n", "-."},
		{"o", "---"}, {"q", "--.-"}, {"r", ".-."}, {"s", "..."}, {"x", "-..-"},
		{"u", "..-"}, {"v", "...-"}, {"w", ".--"}, {"y", "-.--"}, {"z", "--.."},
		{ NULL, NULL } 
	};
	bm = addNodes(bm, characters);

	static entry numbers[] = {
		{"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"},
		{"5", "....."}, {"6", "-...."}, {"7", "--..."}, {"8", "---.."},
		{"9", "----."}, {"0", "-----"}, { NULL, NULL }
	};
	bm = addNodes(bm, numbers);

	bm = addNode(bm, "sos", "...---...");

	char s[2] = " \0"; char c;
	for(c = 'a'; c <= 'z'; ++c) {
		s[0] = c; bMap *n = findNode(bm, s);
		if(!n)
			printf("\tCharacter \"%s\" not found\n", s);
		else
			printf("Value of bm[\"%s\"]: %s\n", s, n->val);
	}
	for(c = '0'; c <= '9'; ++c) {
		s[0] = c; bMap *n = findNode(bm, s);
		if(!n)
			printf("\tCharacter \"%s\" not found\n", s);
		else
			printf("Value of bm[\"%s\"]: %s\n", s, n->val);
	}
	bMap *n = findNode(bm, "sos");
	if(!n)
		printf("\tSOS not found\n");
	else
		printf("SOS found: %s\n", n->val);

	printf("Size of bm: %d\n", bMapSize(bm));
	printf("Size of bm->left: %d\n", bMapSize(bm->left));
	printf("Size of bm->right: %d\n", bMapSize(bm->right));
	printf("Depth of bm: %d\n", bMapDepth(bm));
	printf("Size of bm->left: %d\n", bMapDepth(bm->left));
	printf("Size of bm->right: %d\n", bMapDepth(bm->right));

	deconsBMap(bm);
	return 0;
}
