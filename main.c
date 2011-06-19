#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bMapNode {
	char *key;
	char *val;
	struct bMapNode *left;
	struct bMapNode *right;
} bMap;

bMap *consBMap(char *k, char *v) {
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

bMap *findNode(bMap *bm, char *k) {
	if(!bm || !k) return NULL;
	int cmp = strcmp(bm->key, k);
	if(!cmp)
		return bm;
	if(cmp < 0)
		return findNode(bm->left, k);
	return findNode(bm->right, k);
}

void addNode(bMap *bm, char *k, char *v) {
	if(!bm || !k || !v) return;
	int cmp = strcmp(bm->key, k);
	if(!cmp) {
		if(strcmp(bm->val, v)) {
			free(bm->val);
			bm->val = malloc(strlen(k) + 1);
			strcpy(bm->val, v);
		}
	} else if(cmp < 0) {
		if(!bm->left) {
			bm->left = consBMap(k, v);
		}
		addNode(bm->left, k, v);
	} else {
		if(!bm->right) {
			bm->right = consBMap(k, v);
		}
		addNode(bm->right, k, v);
	}
}

int main(int argc, char **argv) {
	bMap *bm = consBMap("m", "--");
	addNode(bm, "f", "..-.");
	addNode(bm, "c", "-.-.");
	addNode(bm, "a", ".-");
	addNode(bm, "b", "-...");
	addNode(bm, "d", "-..");
	addNode(bm, "e", ".");

	addNode(bm, "i", "..");
	addNode(bm, "g", "--.");
	addNode(bm, "h", "....");
	addNode(bm, "j", ".---");
	addNode(bm, "k", "-.-");
	addNode(bm, "l", ".-..");

	addNode(bm, "t", "-");

	addNode(bm, "p", ".--.");
	addNode(bm, "n", "-.");
	addNode(bm, "o", "---");
	addNode(bm, "q", "--.-");
	addNode(bm, "r", ".-.");
	addNode(bm, "s", "...");

	addNode(bm, "x", "-..-");
	addNode(bm, "u", "..-");
	addNode(bm, "v", "...-");
	addNode(bm, "w", ".--");
	addNode(bm, "y", "-.--");
	addNode(bm, "z", "--..");

	addNode(bm, "1", ".----");
	addNode(bm, "2", "..---");
	addNode(bm, "3", "...--");
	addNode(bm, "4", "....-");
	addNode(bm, "5", ".....");
	addNode(bm, "6", "-....");
	addNode(bm, "7", "--...");
	addNode(bm, "8", "---..");
	addNode(bm, "9", "----.");
	addNode(bm, "0", "-----");

	addNode(bm, "sos", "...---...");

	char s[2] = " \0"; char c;
	for(c = 'a'; c <= 'z'; ++c) {
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

	deconsBMap(bm);
	return 0;
}
