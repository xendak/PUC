#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stdio.h>

#include "util.h"

inline void selection_sort(int* arr) {
  for (int i = 0; i < SRA_ARRAY_SIZE_N - 1; i++) {
    int tmp = i;
    for (int j = i+1; j < SRA_ARRAY_SIZE_N; j++) {
      if (arr[tmp] > arr[j]) {
        tmp = j;
      }
    }
    swap(arr, i, tmp);
  }
}

#endif
