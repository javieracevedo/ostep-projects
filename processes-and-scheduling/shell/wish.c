#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cli_parser.h"
#include "built_in_commands.h"

char *search_path = NULL;
size_t path_buffer_size = 20;

// Built In Commands Names
extern char *EXIT_COMMAND;
extern char *CD_COMMAND;
extern char *PATH_COMMAND;


void handle_system_command(char *command, char **argv, char *redirectFileName) {
  if (search_path != NULL || search_path[0] != 0) { // TODO: consider removing this
    char *path_copy = strdup(search_path);

    char *token;
    char *command_path = "\0";

    while (path_copy != NULL && command_path[0] == '\0') {
      token = strsep(&path_copy, " ");

      char *possible_command_path = strdup(token);
      strcat(possible_command_path, "/");
      strcat(possible_command_path, command);

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
        if (redirectFileName) {
          // TODO: difference between opening a file descriptor and opening a file.
          int fd = open(redirectFileName, O_WRONLY | O_TRUNC);
          if (fd < 0) {
            perror("wish: an error has ocurred");
          }
          dup2(fd, 1);
          dup2(fd, 2);
          close(fd);
        }

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
  add_path_entry(&search_path, "/bin", &path_buffer_size);

  if (argc > 2) {
    fprintf(stderr, "usage: wish <batch.txt> or wish\n");
    free(search_path);
    exit(EXIT_FAILURE);
  }

  char *command_line = NULL;
  size_t command_line_buf_size = 100;
  struct CommandLineInput command_line_input;
  
  system("clear");
  while (1) {
    system("pwd");

    size_t nread = getline(&command_line, &command_line_buf_size, stdin);
    // TODO: maybe just pass the command_line and make the parse function handle empty strings. 
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
        handle_system_command(command_line_input.command, command_line_input.argv, command_line_input.redirectFileName);
      }

      free(command_line_input.argv);
      // free(command_line_input);
    }
  }
}
