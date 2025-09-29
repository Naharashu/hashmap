#include "map.h"

long long TABLE_SIZE = 100000;

//#define NON_STATIC

long long taken = 0;

/*
   Hashmap by Naharashu
   Version 1.3
   MIT LICENSE
*/


Entry** table;

void init_map(long long size) {
	table = calloc(TABLE_SIZE, sizeof(Entry*));
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
			a->value = val;
			return;
		}
		a = a->next;
	}
	#ifdef NON_STATIC
		update_map_size();
	#endif
	Entry* e = malloc(sizeof(Entry));
	e->key = strdup(varname);
	e->value = val;
	e->next = table[i];
	taken++;
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
    long long new_size = TABLE_SIZE;  
    if (taken > (TABLE_SIZE * 0.75)) {
        new_size = (long long)(TABLE_SIZE * 1.25); 
        new_size = rescale_map(new_size);  
        if (new_size != 0) {  
            memset(table + TABLE_SIZE, 0, (new_size - TABLE_SIZE) * sizeof(Entry*));  // Правильне використання таблиці
        }
    }
    TABLE_SIZE = new_size;  
}
