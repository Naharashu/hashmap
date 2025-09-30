#include "map.h"
#include <stdint.h>

long long TABLE_SIZE = 10000000;

//#define NON_STATIC

long long taken = 0;

/*
   Hashmap by Naharashu
   Version 1.4
   MIT LICENSE
*/


Entry** table;

void init_map(long long size) {
	table = calloc(size, sizeof(Entry*));
	TABLE_SIZE = size;
}


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
			a->value.v = &val;
			return;
		}
		a = a->next;
	}
	#ifdef NON_STATIC
		update_map_size();
	#endif
	Entry* e = malloc(sizeof(Entry));
	e->key = strdup(varname);
	e->value.v = (void*)(intptr_t)val;
	e->next = table[i];
	taken++;
	table[i] = e;
}

void* get(char *name) {
	int i = indx(name);
	Entry* e = table[i];
	while(e) {
		if(strcmp(e->key, name) == 0) {
			return e->value.v;
		}
		e = e->next;
	}
	return NULL;
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
		taken--;
	}
}


long long rescale_map(long long size) {
	Entry** tmp = realloc(table, size*sizeof(Entry*));
	if(!tmp) {
		free_table();
		return 0;
	}
	table = tmp;
	return size;
}

void update_map_size() {
    if (taken <= (TABLE_SIZE * 0.75)) return;

    long long old_size = TABLE_SIZE;
    long long new_size = (long long)(TABLE_SIZE * 1.25);

    Entry** new_table = calloc(new_size, sizeof(Entry*));
    if (!new_table) {
        return;
    }

    for (long long i = 0; i < old_size; i++) {
        Entry* e = table[i];
        while (e) {
            Entry* next = e->next;

            int new_index = ((unsigned int)(hash(e->key)) % new_size);
            e->next = new_table[new_index];
            new_table[new_index] = e;

            e = next;
        }
    }

    free(table); 
    table = new_table;
    TABLE_SIZE = new_size;
}
