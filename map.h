#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Entry {
	char *key;
	int value;
	struct Entry *next;
} Entry;

static inline int hash(char* str);
static inline int indx(char* str);
void set(char* varname, int val);
int get(char *name);
void free_table();

#endif
