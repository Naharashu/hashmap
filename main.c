#include <time.h>
#include "map.h"

// включаємо твою хеш-таблицю тут

int main() {
    init_map(100000);    
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
