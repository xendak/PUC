#include <stdio.h>

void swap(int arr[], int i, int j) {
  int t = arr[i];
  arr[i] = arr[j];
  arr[j] = t;
}

void selection_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    int tmp = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[tmp] > arr[j]) {
        tmp = j;
      }
    }
    swap(arr, i, tmp);
  }
}

int main() {
  int n;
  int kv;
  while (scanf(",") != EOF) {
    if (scanf("%d %d", &n, &kv) != 2) {
      return 1;
    }
    int arr[n];
    for (int i = 0; i < n; i++) {

      if(scanf("%d", &arr[i]) != 1) return 1;
    }
    selection_sort(arr, n);

    int sum = 0;
    for (int i = 0; i < kv; i++) {
      sum = sum + arr[n - i - 1];
    }
    printf("%d\n", sum);
  }
  return 0;
}
