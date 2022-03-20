#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  char buffer[8];
  for (int i=1 ; argv[i]; i++) {
    file = fopen(argv[i], "r");
    if (!file) {
      printf("wcat: cannot open file\n");
      exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof buffer, file) != NULL)
      printf("%s", buffer);
    

    if(ferror(file)) {
      perror("wcat: cannot read content of file");
      fclose(file);
      exit(EXIT_FAILURE);
    }

    if (fclose(file) != 0) {
      perror("wcat: cannot close file");
      exit(EXIT_FAILURE);
    };
  }

  exit(EXIT_SUCCESS);
}