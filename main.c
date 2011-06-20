#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmap.h"

int main(int argc, char **argv) {
	bMap *bm = consBMap("M", "--"); 
	static entry characters[] = { 
		{"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."}, {"E", "."},
		{"F", "..-."}, {"G", "--."}, {"H", "...."}, {"I", ".."}, {"J", ".---"},
		{"K", "-.-"}, {"L", ".-.."}, {"M", "--"}, {"N", "-."}, {"O", "---"},
		{"P", ".--."}, {"Q", "--.-"}, {"R", ".-."}, {"S", "..."}, {"T", "-"},
		{"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"}, {"Y", "-.--"},
		{"Z", "--.."}, { NULL, NULL }
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
	for(c = ' '; c <= '_'; ++c) {
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
	printf("\tbm->left: %d\n", bMapSize(bm->left));
	printf("\tbm->right: %d\n", bMapSize(bm->right));
	printf("Depth of bm: %d\n", bMapDepth(bm));
	printf("\tbm->left: %d\n", bMapDepth(bm->left));
	printf("\tbm->right: %d\n", bMapDepth(bm->right));

	deconsBMap(bm);
	return 0;
}
