#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *bubble_sort(char *str, size_t size) {
  for (int i = 0; i < size; i++) {
    for (int j=0; j<=size - i - 1; j++) {
      if (str[j+1] == '\n' || str[j+1] == '\0') continue;
      if (str[j] > str[j+1]) {
        char tmp = str[j];
        str[j] = str[j+1];
        str[j+1] = tmp;
      }
    }
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
  while ((nread = getline(&buffer, &buffer_size, input_stream)) != -1) {
    char *sorted_line = bubble_sort(buffer, nread);
    fwrite(sorted_line, sizeof(char), nread, output_stream);
  }

  fclose(input_stream);
  fclose(output_stream);
}

