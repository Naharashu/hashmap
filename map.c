#include "map.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE 100000
#endif

/*
   Hashmap by Naharashu
   Version 1.2
   MIT LICENSE
*/


Entry* table[TABLE_SIZE] = {0};


static inline int hash(char *str) {
	register unsigned int i=0;
	int len = strlen(str);
	for(int j = 0; j<len;j++) {
		// i = str[j] + (i << 6) + (i << 16) - i;
		i = str[j] + i * 65599;
	}
	return i;
}

static inline int indx(char *str) {
	return ((unsigned int)(hash(str)) % TABLE_SIZE);
}

void set(char *varname, int val) {
	int i = indx(varname);
	Entry* a = table[i];
	while(a) {
		if(__builtin_expect(strcmp(a->key, varname)==0, 0)) {
			a->value = val;
			return;
		}
		a = a->next;
	}
	Entry* e = malloc(sizeof(Entry));
	e->key = strdup(varname);
	e->value = val;
	e->next = table[i];
	table[i] = e;
}

int get(char *name) {
	int i = indx(name);
	Entry* e = table[i];
	while(e) {
		if(strcmp(e->key, name) == 0) {
			return e->value;
		}
		e = e->next;
	}
	return -1;
}

void free_table() {
	for(int i = 0; i < TABLE_SIZE; i++) {
		Entry* e = table[i];
		while(e) {
			Entry* next = e->next;
			free(e->key);
			free(e);
			e = next;
		}
		table[i] = NULL;
	}
}
