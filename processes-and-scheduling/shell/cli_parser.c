#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "cli_parser.h"

#include <stdio.h>

char* trim_spaces(const char *string, size_t string_length) {
  const char *start = string;
  const char *end = string + string_length - 1;

  // Skip leading spaces
  while (start <= end && *start == ' ') {
    start++;
  }

  // Skip trailing spaces
  while (end >= start && *end == ' ') {
    end--;
  }

  // Allocate a new string and copy the trimmed substring
  size_t trimmed_length = end - start + 1;
  char *trimmed_string = malloc(trimmed_length + 1);
  memcpy(trimmed_string, start, trimmed_length);
  trimmed_string[trimmed_length] = '\0';

  return trimmed_string;
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

  parsed_commands = calloc(count, sizeof(struct CommandLineInput));
  for (int i=0; i<count; i++) {
    size_t command_length = strlen(commands[i]);
    char *trimmed_command = trim_spaces(commands[i], command_length);
    parsed_commands[i] = parse_command(trimmed_command, strlen(commands[i]));
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
    size_t redirect_file_name_length = strlen(command_line_input.redirectFileName);
    trim_spaces(command_line_input.redirectFileName, redirect_file_name_length);
  }

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
  if (struct_array == NULL) {
    printf("struct_array is NULL\n");
  }
  int count = 0;
  while (struct_array->command != NULL) {
    // if (struct_array->command != NULL) {¡
      printf("%s\n", struct_array->command);
      struct_array++;
      count++;
    // }
  }
  return count;
}
