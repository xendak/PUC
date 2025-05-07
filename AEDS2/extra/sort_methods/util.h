#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#ifndef SRA_ARRAY_SIZE_N
#define SRA_ARRAY_SIZE_N 10000
#endif

#ifndef SRA_RANDOM_MIN_VAL
#define SRA_RANDOM_MIN_VAL 1
#endif

#ifndef SRA_RANDOM_MAX_VAL
#define SRA_RANDOM_MAX_VAL 1000
#endif

#ifndef ITEM_COUNT_TO_PRINT
#define ITEM_COUNT_TO_PRINT 100
#endif


static int sra_internal_array[(SRA_ARRAY_SIZE_N > 0) ? SRA_ARRAY_SIZE_N : 1];
static int sra_is_initialized = 0;
static int sra_srand_has_been_called = 0;

typedef enum {
  FALSE,
  TRUE,
} bool;

void swap(int* arr, int src, int dst) {
  int tmp = arr[src];
  arr[src] = arr[dst];
  arr[dst] = tmp;
}

static void sra_fill_array_contents(int* arr, size_t size) {
    if (size == 0) return;

    if (!sra_srand_has_been_called) {
        srand((unsigned int)time(NULL));
        sra_srand_has_been_called = 1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (SRA_RANDOM_MAX_VAL < SRA_RANDOM_MIN_VAL) {
            arr[i] = SRA_RANDOM_MIN_VAL;
        } else {
            // Formula: rand() % (upper - lower + 1) + lower
            arr[i] = (rand() % (SRA_RANDOM_MAX_VAL - SRA_RANDOM_MIN_VAL + 1)) + SRA_RANDOM_MIN_VAL;
        }
    }
}

int* get_static_random_array(void) {
    if (SRA_ARRAY_SIZE_N <= 0) {
        return NULL;
    }

    if (!sra_is_initialized) {
        sra_fill_array_contents(sra_internal_array, SRA_ARRAY_SIZE_N);
        sra_is_initialized = 1;
    }
    return sra_internal_array;
}

void rerandomize_static_array(void) {
    if (SRA_ARRAY_SIZE_N <= 0) {
        return;
    }

    if (!sra_is_initialized) {
        get_static_random_array();
    } else {
        sra_fill_array_contents(sra_internal_array, SRA_ARRAY_SIZE_N);
    }
}

void print_array(const int* arr, size_t size, const char* label) {
    if (arr == NULL || size == 0) {
        printf("%s: Array is NULL or empty.\n", label);
        return;
    }
    printf("%s (first %zu elements): ", label, (size < ITEM_COUNT_TO_PRINT ? size : ITEM_COUNT_TO_PRINT));
    for (size_t i = 0; i < size && i < ITEM_COUNT_TO_PRINT; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#endif
