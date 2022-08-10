#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct CommandLineInput {
  char *command;
  int argc;
  char *args;
  char *argv[100];
  int empty;
} CommandLineInput;


CommandLineInput *parse_command_line(char *command_line, size_t nread) {
  struct CommandLineInput *command_line_input;
  if ((command_line_input = malloc(sizeof(struct CommandLineInput))) == NULL) {
    fprintf(stderr, "creation of CommandLineInput struct failed\n");
  }

  command_line[nread - 1] = '\0'; // get read of the \n special character
  command_line_input->command = strsep(&command_line, " "); // TODO: this eventually will need to handle operators like >
  command_line_input->args = command_line;

  int idx = 0;
  while (command_line != NULL) {
    char *token = strsep(&command_line, " ");
    command_line_input->argv[idx] = malloc(sizeof(char *));
    command_line_input->argv[idx] = token;
    idx++;
  }

  if (command_line_input->argv[0] != NULL) {
    printf("%s\n", command_line_input->argv[0]);
  }

  return command_line_input;
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    fprintf(stderr, "usage: wish <batch.txt> or wish\n");
    exit(EXIT_FAILURE);
  }

  char *path = "/bin";
  // Built In Commands Names
  char *EXIT_COMMAND = "exit";
  char *CD_COMMAND = "cd";
  char *PATH_COMMAND = "path";

  char *command_line = NULL;
  size_t command_line_buf_size = 0;
  
  int running = 1;
  while (running) {
    system("pwd");

    size_t nread = getline(&command_line, &command_line_buf_size, stdin);
    CommandLineInput *command_line_input = parse_command_line(command_line, nread);

    if (strcmp(command_line_input->command, EXIT_COMMAND) == 0) {
      if (!command_line_input->args) {
        exit(EXIT_FAILURE);
      } 
      fprintf(stderr, "exit: too many arguments\n");
    } else if (strcmp(command_line_input->command, CD_COMMAND) == 0) {
      if (chdir(command_line_input->args) == -1) {
        fprintf(stderr, "An error has ocurred\n");
      }
    } else if (strcmp(command_line_input->command, PATH_COMMAND) == 0) {
      path = command_line_input->args;
      printf("%s\n", path);
    } else {
      if (path[0] != '\0') { // TODO: consider removing this
        char *path_copy = strdup(path);

        char *token;
        char *command_path = "\0";

        while (path_copy != NULL && command_path[0] == '\0') {
          token = strsep(&path_copy, " ");

          char *possible_command_path = strdup(token);
          strcat(possible_command_path, "/");
          strcat(possible_command_path, command_line_input->command);

          if (access(possible_command_path, X_OK) == 0) {
            command_path = strdup(possible_command_path);
          }
        }

        if (command_path[0] == '\0') {
          fprintf(stderr, "wish: could not find %s command\n", command_line_input->command);
        } else {
          char *newargv[] = { };
          char *newenviron[] = { NULL };

          int error;
          if ((error = execv(command_path, newargv)) != 0) {
            perror("wish: An error has ocurred");
          }
        }
      } else {
        printf("wish: path is not set");
      }
    }
  }
}
