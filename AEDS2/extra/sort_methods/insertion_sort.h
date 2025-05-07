#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stdio.h>

#include "util.h"

inline void insertion_sort(int* arr) {
  for (int i = 1; i < SRA_ARRAY_SIZE_N - 1; i++) {
    int j = i - 1; // we get 1 before the key.
    int key = arr[i];

    // WORKS BY
    // the idea of everything before I being already sorted.

    // if j is still going backwards ( j > 0)
    // and key is still less than what we are currently at.
    // shift left;
    while(j >= 0 && key < arr[j]) {
      arr[j-1] = arr[j];
      j--;
    }
    // we swap next, we what we began since that is the correct
    // position, because everything that was wrong was shifted.
    arr[j+i] = key;
  }
}

#endif
