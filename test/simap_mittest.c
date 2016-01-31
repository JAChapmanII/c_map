#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simap.h"

int qsort_strcmp(const void *a, const void *b);
int qsort_strcmp(const void *a, const void *b) {
	const char **sa = (const char **)a;
	const char **sb = (const char **)b;
	return strcmp(*sa, *sb);
}

int main(int argc, char **argv) {
	srand(time(NULL));
	int nodeCount = 16;
	if(argc > 1) {
		nodeCount = atoi(argv[1]);
		if(nodeCount == 0)
			nodeCount = 16;
	}

	SIMap_Iterator *it = simapi_create();
	if(!it) {
		fprintf(stderr, "test: could not create SIMap_Iterator\n");
		return 1;
	}

	SIMap *map = simap_create();
	if(!map) {
		fprintf(stderr, "test: could not create SIMap\n");
		return 1;
	}

	simap_find(map, "5");

	char key[80], *keys[nodeCount];
	uint32_t val = 5;
	printf("Adding: ");
	for(int i = 0; i < nodeCount; ++i) {
		snprintf(key, 80, "%u", val);
		keys[i] = strdup(key);
		printf("%s", key);
		if(i != nodeCount - 1)
			printf(", ");
		simap_set(map, key, val);
		val += (rand() % 3) + 1;
	}
	printf("\n");

	qsort(keys, nodeCount, sizeof(char *), qsort_strcmp);
	for(int i = 0; i < nodeCount; ++i) {
		printf("%s", keys[i]);
		if(i != nodeCount - 1)
			printf(", ");
	}
	printf("\n");


	simapi_front(it, map);
	printf("Testing forward iterator (fit)\n");
	int seen = 0;
	while(it->type != IT_END) {
		seen++;
		if(strcmp(it->current->key, keys[seen - 1]) != 0)
			fprintf(stderr, "test: expected key does not match current [fit] "
					"\"%s\" != \"%s\"\n", it->current->key, keys[seen - 1]);
		simapi_next(it);
	}
	if(seen != nodeCount) {
		fprintf(stderr, "test: seen != nodeCount [fit]\n");
		return 3;
	}

	simapi_back(it, map);
	printf("Testing reverse iterator (rit)\n");
	seen = 0;
	while(it->type != IT_BEGIN) {
		seen++;
		if(strcmp(it->current->key, keys[nodeCount - seen]) != 0)
			fprintf(stderr, "test: expected key does not match currrent [rit]\n");
		simapi_prev(it);
	}
	if(seen != nodeCount) {
		fprintf(stderr, "test: seen != nodeCount [rit]\n");
		return 3;
	}

	printf("Everything good\n");
	return 0;
}

