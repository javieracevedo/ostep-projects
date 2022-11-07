#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "cli_parser.h"

#include <stdio.h>

// TODO: try to improve/simplify this function's logic
void trim_spaces(char **string) {
  int leading_spaces_count = 0;
  for (int i=0; (*string)[i] == ' '; i++) leading_spaces_count++;

  int trailing_spaces_count = 0;
  for (int j=strlen(*string) - 1; (*string)[j] == ' '; j--) trailing_spaces_count++;

  int left_idx = 0;

  if (leading_spaces_count > 0) {
    int right_idx = leading_spaces_count;
    while ((*string)[right_idx] != '\0') {
      (*string)[left_idx] = (*string)[right_idx];
      (*string)[right_idx] = ' '; // Maybe we could set to null r-ight away?
      left_idx++;
      right_idx++;
    }
  }
  
  (*string)[strlen(*string) - (leading_spaces_count + trailing_spaces_count)] = '\0';
}


struct CommandLineInput* parse_command_line(char *command_line, size_t command_line_length) {
  char **commands = NULL;
  struct CommandLineInput* parsed_commands = NULL;

  if (strcmp(command_line, "\n") == 0) {
    return parsed_commands;
  }

  command_line[command_line_length - 1] = '\0'; // get rid of the \n special character

  commands = malloc(sysconf(_SC_ARG_MAX));
  int count = 0;
  while (command_line != NULL) {
    char *command = strsep(&command_line, "&");
    commands[count] = command;
    count++;
  }
  commands[count] = NULL;

  // TODO: check the initialization of this, shouldn't this have count amount of structs?
  parsed_commands = calloc(count, sizeof(struct CommandLineInput));
  for (int i=0; i<count; i++) {
    trim_spaces(&commands[i]);
    parsed_commands[i] = parse_command(commands[i], strlen(commands[i]));
  }

  return parsed_commands;
}

struct CommandLineInput parse_command(char *command, size_t command_line_length) {
  struct CommandLineInput command_line_input = {NULL, 0, NULL};

  // If the command line is empty (meaning it only has a line feed character and a null character)
  // return empty command line input struct
  if (command_line_length <= 1) {
    return command_line_input;
  }
  
  char *lhs = strsep(&command, ">");

  // if there is something left in the command line after separating by >, it means there is a RHS, which should be the name of the file to redirec to
  if (command) {
    command_line_input.redirectFileName = command;
    trim_spaces(&command_line_input.redirectFileName);
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


int command_line_input_struct_array_length(CommandLineInput *struct_array) {
  int count = 0;
  while (struct_array->command != NULL) {
    struct_array++;
    count++;
  }
  return count;
}