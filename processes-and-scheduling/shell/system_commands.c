#include "system_commands.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "error_handling.h"

extern char *search_path;


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
      print_error(-1);
    } else { 
      if (redirectFileName) {
        // TODO: difference between opening a file descriptor and opening a file.
        int fd = open(redirectFileName, O_WRONLY | O_TRUNC);
        if (fd < 0) {
          print_error(fd);
          exit(EXIT_SUCCESS);
          // TODO: should we exit with error here, or exit normally since the error is handled another way?
          // or maybe just we the redirect file name in the outer function?
        }
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
      }
      
      if (execv(command_path, argv) != 0) {
        exit(EXIT_FAILURE);
      }
    }
  } else {
    exit(EXIT_FAILURE);
  }
}

void execute_commands(CommandLineInput *commands, int length) {
  int pid = -1;
  for (int i=0; i<length; i++) {
    // Fork again, only if process is the parent (pid != 0)
    if (pid != 0) {
      pid = fork(); 
      // Attempt to execute sys command, only if process is a child (pid == 0)
      if (pid == 0) {
        handle_system_command(commands[i].command, commands[i].argv, commands[i].redirectFileName);
      }
    }
  }

  int rc;
  int status;
  while ((rc = wait(&status)) != -1)
    if (status != 0)
      print_error(status);
}
