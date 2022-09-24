#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "array_lib.h"
#include <sys/wait.h>

struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
};


char *search_path = NULL;
size_t path_buffer_size = 20;


struct CommandLineInput parse_command_line(char *command_line, size_t command_line_length) {
  struct CommandLineInput command_line_input = {NULL, 0, NULL};

  // basically, if command line is empty (meaning it only has a line feed character and a null character)
  // return empty command line input struct
  if (command_line_length <= 1) {
    return command_line_input;
  }

  // TODO: check the speed of this function, with stack allocation vs heap allocation
  //  = { .command = '', .argc = 0, .argv = {}};
  // if ((command_line_input = malloc(sizeof(struct CommandLineInput))) == NULL) {
  //   fprintf(stderr, "creation of CommandLineInput struct failed\n");
  //   // Instead of priting, set error and print elsewhere with perror?
  //   return NULL;
  // }

  command_line[command_line_length - 1] = '\0'; // get rid of the \n special character

  int count = 0;
  // TODO: try to avoid doing this everytime. Could we do this one, and clear it?
  command_line_input.argv = calloc(100, sizeof(char *));
  while (command_line != NULL) {
    char *token = strsep(&command_line, " ");
    command_line_input.argv[count] = token;
    count++;
  }
  command_line_input.argv[count] = NULL;
  command_line_input.argc = count;
  command_line_input.command = command_line_input.argv[0];

  // free(command_line);
  return command_line_input;
}

// Built In Commands Names

char *EXIT_COMMAND = "exit";
char *CD_COMMAND = "cd";
char *PATH_COMMAND = "path";

int add_path_entry(char **search_path, char *new_entry, size_t *buffer_size) {
  if (*search_path == NULL) {
    if((*search_path = calloc(200, sizeof(char))) == NULL) {
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
  // *search_path[strlen(*search_path)];
  return 0;
}

void handle_exit_command(int argc){
  if (argc > 1) {
    fprintf(stderr, "exit: too many arguments\n");
  } else {
    exit(EXIT_FAILURE);
  }
}

void handle_cd_command(int argc, char **argv) {
  if (argc > 2) {
    fprintf(stderr, "cd: too many arguments\n");
    return;
  } else if (argc < 2) {
    fprintf(stderr, "cd: too few arguemnts\n");
    return;
  } 
  
  if (chdir(argv[1]) == -1) {
    fprintf(stderr, "An error has ocurred\n");
  }
}

void handle_path_command(int argc, char **argv) {
  for (int i=1; i<argc; i++) {
    add_path_entry(&search_path, argv[i], &path_buffer_size);
  }
}

void handle_built_in_command(char *command, int argc, char **argv) {
  if (strcmp(command, CD_COMMAND) == 0) {
    handle_cd_command(argc, argv);
  } else if (strcmp(command, PATH_COMMAND) == 0) {
    handle_path_command(argc, argv);
  }
}

void handle_system_command(char *command, char **argv) {
  if (search_path != NULL || search_path[0] != 0) { // TODO: consider removing this
    char *path_copy = strdup(search_path);

    char *token;
    char *command_path = "\0";

    while (path_copy != NULL && command_path[0] == '\0') {
      token = strsep(&path_copy, " ");

      char *possible_command_path = strdup(token);
      strcat(possible_command_path, "/");
      strcat(possible_command_path, command);

      // TODO: check why access is not finding my custom programs
      if (access(possible_command_path, X_OK) == 0) {
        command_path = strdup(possible_command_path);
      }
    }

    if (command_path[0] == '\0') {
      fprintf(stderr, "wish: could not find %s command\n", command);
    } else {
      int pid = fork();
      if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      }

      if (pid == 0) {
        int error;
        if ((error = execv(command_path, argv)) != 0) {
          perror("wish: an error has ocurred");
        }
      } else {
        wait(NULL);
      }
    }
  } else {
    printf("wish: path is not set");
  }
}

int main(int argc, char *argv[]) {
  // for (int i=0; __environ[i]; i++) {
  //   printf("%s\n", __environ[i]);
  // }
  // exit(0);
  add_path_entry(&search_path, "/bin", &path_buffer_size);

  if (argc > 2) {
    fprintf(stderr, "usage: wish <batch.txt> or wish\n");
    free(search_path);
    exit(EXIT_FAILURE);
  }

  char *command_line = NULL;
  size_t command_line_buf_size = 100;
  struct CommandLineInput command_line_input;

  while (1) {
    system("pwd");

    size_t nread = getline(&command_line, &command_line_buf_size, stdin);
    command_line_input = parse_command_line(command_line, nread);
    
    if (command_line_input.command) {
      if (strcmp(command_line_input.command, CD_COMMAND) == 0 || strcmp(command_line_input.command, PATH_COMMAND) == 0) {
        handle_built_in_command(command_line_input.command, command_line_input.argc, command_line_input.argv);
      } else if (strcmp( command_line_input.command, EXIT_COMMAND) == 0) { // TODO: handle ctrl+c and ctrl+d
        if (command_line_input.argc <= 1) {
          free(command_line);
          free(command_line_input.argv);
          free(search_path);
          exit(EXIT_FAILURE);
        }

        fprintf(stderr, "exit: too many arguments\n");
       
      } else {
        // TODO: handle system command
        handle_system_command(command_line_input.command, command_line_input.argv);
      }

      free(command_line_input.argv);
      // free(command_line_input);
    }
  }
}

