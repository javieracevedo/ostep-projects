#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_4_byte_binary(char *compressed_chunk) {
  int current_partial_int = compressed_chunk[3];
  for (int i=2; i >= 0; i--) {
    current_partial_int = (current_partial_int << 8) | compressed_chunk[i];
  }

  return current_partial_int;
}

char *reverse_rle(char compressed_chunk[]) {
  char character = compressed_chunk[4];
  int character_count = read_4_byte_binary(compressed_chunk);
  char *uncompressed_string = malloc(character_count + 1);
  for (int i=0; i < character_count; i++)
    uncompressed_string[i] = character;

  return uncompressed_string;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  char compressed_chunk[5];

  for (int i=1; i < argc; i++) {
    char *file_name = argv[i];
    if ((file = fopen(file_name, "r")) == NULL) {
      perror("wzip: cannot open file");
      exit(EXIT_FAILURE);
    }

    while (fread(&compressed_chunk, 5, 1, file)) {
      char *uncompressed_string = reverse_rle(compressed_chunk);
      printf("%s", uncompressed_string);
    }
    fclose(file);
  }
}