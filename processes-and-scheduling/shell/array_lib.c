#include <stdio.h>
#include <stdlib.h>
#include "array_lib.h"
#include <string.h>

int get_array_length(char **array) {
  int count = 0;
  while (*array != NULL) {
    array++;
    // printf("%s\n", *array);
    count++;
  }

  return count;
}

// TODO: wrap array in a struct and keep track of the non null elements of the array
// and resize (realloc) when the array is full. This would help us get rid of checking
// the length of the array each to we want to push to the end.
int str_array_push_end(char ***array, char *new_element, size_t *buffer_size) {
  int array_len = get_array_length(*array); // We could avoid this by somehow keeping track of the elements added to the array each time.
  if (array_len >= *buffer_size - 1) {
    size_t new_buffer_size = *buffer_size * 2;

    if ((*array = realloc(*array, new_buffer_size * sizeof(char *))) == NULL) {
      fprintf(stderr, "realloc failed");
      return -1;
    }

    *buffer_size = *buffer_size * 2;
  }

  *array[array_len] = new_element;
  return 0;
}
