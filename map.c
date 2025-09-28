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
	int a = (unsigned int)(hash(str)) % TABLE_SIZE;
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


/*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// включаємо твою хеш-таблицю тут

int main() {
    const int N = 100000; // кількість ключів
    char key[20];
    clock_t start, end;

    // Вставка
    start = clock();
    for(int i = 0; i < N; i++) {
        sprintf(key, "key%d", i);
        set(key, i);
    }
    end = clock();
    printf("Insertion of %d keys took %.3f seconds\n", N, (double)(end - start)/CLOCKS_PER_SEC);

    // Пошук
    start = clock();
    for(int i = 0; i < N; i++) {
        sprintf(key, "key%d", i);
        int val = get(key);
        if(val != i) {
            printf("Error at key %d\n", i);
        }
    }
    end = clock();
    printf("Lookup of %d keys took %.3f seconds\n", N, (double)(end - start)/CLOCKS_PER_SEC);

    free_table();
    return 0;
}

*/