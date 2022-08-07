#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *bubble_sort(char *str, size_t size) {
  for (int i = 0; i < size; i++) {
    for (int j=0; j<=size - i - 1; j++) {
      if (str[j+1] == '\n' || str[j+1] == '\0') break;
      if (str[j] > str[j+1]) {
        char tmp = str[j];
        str[j] = str[j+1];
        str[j+1] = tmp;
      }
    }
  }
  return str;
}

static char *insertion_sort(char *str, size_t size) {
  int j;
  char current_char;
  for (int i=1; i < size; i++) {
    if (str[i] == '\n' || str[i] == '\0') break;

    current_char = str[i];
    j = i - 1;
    
    while (j >= 0 && str[j] > current_char) {
      str[j + 1] = str[j];
      j = j - 1;
    }
    str[j + 1] = current_char; // why j + 1? doesn't that ignore the first char always?
  }
  return str;
}


int main(int argc, char *argv[]) {
  if (argc >= 4) {
    fprintf(stderr, "usage: sort-text <input> <output>\n");
    exit(EXIT_FAILURE);
  }

  char *input_file_name = argv[1];
  char *output_file_name = argv[2];

  FILE *input_stream = argc <= 1 ? stdin : fopen(input_file_name, "r");
  FILE *output_stream = argc <= 2 ? stdout : fopen(output_file_name, "w");

  if (!input_stream || !output_stream) {
    fprintf(stderr, "sort-text: cannot open file '%s'\n", !input_stream ? input_file_name : output_file_name);
    exit(EXIT_FAILURE);
  }

  // TODO: understand this double pointer stuff
  // char **sorted_lines_array;

  char *buffer = '\0';
  size_t buffer_size = sizeof(char *);
  size_t nread;

  clock_t begin = clock();

  while ((nread = getline(&buffer, &buffer_size, input_stream)) != -1) {
    // char *sorted_line = bubble_sort(buffer, nread);
    char *sorted_line = insertion_sort(buffer, nread);
    fwrite(sorted_line, sizeof(char), nread, output_stream);
  }

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  
  printf("Time spent: %f\n", time_spent);

  fclose(input_stream);
  fclose(output_stream);
  free(buffer);
}
