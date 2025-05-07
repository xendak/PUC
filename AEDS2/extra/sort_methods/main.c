
#define SRA_ARRAY_SIZE_N 10

#include "util.h"
#include "bubble_sort.h"  
#include "selection_sort.h"  
#include "insertion_sort.h"  


int main() {
  printf("Starting\n");
  int* data = get_static_random_array();

  printf("\nBubble\n");
  print_array(data, SRA_ARRAY_SIZE_N, "Original array");
  bubble_sort(data);
  print_array(data, SRA_ARRAY_SIZE_N, "Sorted array  ");

  rerandomize_static_array();
  printf("\nSelection\n");
  print_array(data, SRA_ARRAY_SIZE_N, "Original array");
  selection_sort(data);
  print_array(data, SRA_ARRAY_SIZE_N, "Sorted array  ");

  rerandomize_static_array();
  printf("\nInsertion\n");
  print_array(data, SRA_ARRAY_SIZE_N, "Original array");
  insertion_sort(data);
  print_array(data, SRA_ARRAY_SIZE_N, "Sorted array  ");
  
}
