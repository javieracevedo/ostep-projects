#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "built_in_commands.h"
#include "error_handling.h"

extern char *search_path;
extern size_t path_buffer_size;

// Built In Commands Names
char *EXIT_COMMAND = "exit";
char *CD_COMMAND = "cd";
char *PATH_COMMAND = "path";


int add_path_entry(char **search_path, char *new_entry, size_t *buffer_size) {
  if (*search_path == NULL) {
    if((*search_path = calloc(*buffer_size, sizeof(char))) == NULL) {
      // Should we set an error or something here? to be printed with perror
      return -1;
    }
  }

  size_t next_search_path_size = strlen(*search_path) + strlen(new_entry);
  if (next_search_path_size >= *buffer_size - 1) {
    size_t new_buffer_size = *buffer_size * 2;
    if((*search_path = realloc(*search_path, new_buffer_size * sizeof(char))) == NULL) {
      // Should we set an error or something here? to be printed with perror
      return -1;
    }
    *buffer_size = new_buffer_size;
  }

  if (*search_path[0] != '\0') {
    strcat(*search_path, " ");
  }

  strcat(*search_path, new_entry);
  return 0;
}

int handle_exit_command(int argc){
  if (argc != 1) return -1;
  exit(EXIT_FAILURE);
}

int handle_cd_command(int argc, char **argv) {
  if (argc != 2) return -1;
  if (chdir(argv[1]) == -1) return -1;
  return 0;
}

int handle_path_command(int argc, char **argv) {
  for (int i=1; i<argc; i++) {
    int return_code = add_path_entry(&search_path, argv[i], &path_buffer_size);
    if (return_code < 0) return return_code;
  }
  return 0;
}

int handle_built_in_command(char *command, int argc, char **argv) {
  if (strcmp(command, CD_COMMAND) == 0) {
    return handle_cd_command(argc, argv);
  } else if (strcmp(command, PATH_COMMAND) == 0) {
    return handle_path_command(argc, argv);
  }
  return -1;
}
