#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TABLE_SIZE
#define TABLE_SIZE 1024
#endif

/*
   Hashmap by Naharashu
   Version 1.1
   MIT LICENSE
*/

typedef struct Entry {
	char *key;
	int value;
	struct Entry *next;
} Entry;

Entry* table[TABLE_SIZE] = {0};

int hash(char *str) {
	int i = 0;
	int len = strlen(str);
	for(int j = 0; j < len; j++) {
		i = str[j] + (i << 6) + (i << 16) - i;
	}
	return i;
}

int indx(char *str) {
	int a = hash(str) % TABLE_SIZE;
	return a;
}

void set(char *varname, int val) {
	int i = indx(varname);
	Entry* e = malloc(sizeof(Entry));
	e->key = varname;
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
