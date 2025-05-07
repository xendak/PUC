#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stdio.h>

#include "util.h"


// can be optimized by having
// 1. reducing legnth by 1 every iteration of a sorted TRUE; since last item is always sorted
// 2. if a swap happens you can set new size to be its index. (so you loop less each iteration)
inline void bubble_sort(int* arr) {
  size_t n = SRA_ARRAY_SIZE_N;
  while (n >= 1) {
    size_t new_size = 0;
    for(int i = 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        swap(arr, i-1, i);
        new_size = i;
      }
    }
    n = new_size;
  }  
}

#endif
