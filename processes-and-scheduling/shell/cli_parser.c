#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "cli_parser.h"

struct CommandLineInput parse_command_line(char *command_line, size_t command_line_length) {
  struct CommandLineInput command_line_input = {NULL, 0, NULL};

  // If the command line is empty (meaning it only has a line feed character and a null character)
  // return empty command line input struct
  if (command_line_length <= 1) {
    return command_line_input;
  }

  command_line[command_line_length - 1] = '\0'; // get rid of the \n special character
  
  char *lhs = strsep(&command_line, ">");

  // if there is something left in the command line after separating by >, it means there is a RHS, which is the redirect fileName
  if (command_line) {
    command_line_input.redirectFileName = command_line;
  }
  
  // TODO: try to do this only once, outside of this function call. Maybe we could check if we need to do it or not first.
  command_line_input.argv = malloc(sysconf(_SC_ARG_MAX));
  while (lhs != NULL) {
    char *token = strsep(&lhs, " ");
    if (strcmp(token, "") != 0) {
      command_line_input.argv[command_line_input.argc] = token;
    }
    command_line_input.argc++;
  }
  command_line_input.argv[command_line_input.argc] = NULL;
  command_line_input.command = command_line_input.argv[0];

  return command_line_input;
}