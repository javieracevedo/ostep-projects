#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli_parser.h"

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


struct CommandLineInput parse_command(char *command, size_t command_line_length) {
  // QUESTION: why can I return a struct defined in the stack here?, because I'm not returning a pointer from it?
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


struct CommandLineInput* parse_command_line(char *command_line, size_t command_line_length) {
  char **commands = NULL;
  struct CommandLineInput* parsed_commands = NULL;

  if (strcmp(command_line, "\n") == 0) {
    return parsed_commands;
  }

  // CHECK: this has to be a bug, or I don't get something
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


struct CommandLineConfig parse_config_file_line(char *config_file_line, size_t config_file_line_length) {
  // QUESTION: What's gonna happend with all the unused space, does that cause memory issues? 
  char *lhs = malloc(1000);
  char *rhs = malloc(1000);
  struct CommandLineConfig parsed_config_line = { NULL, NULL };

  if (strcmp(config_file_line, "\n") == 0) {
    return parsed_config_line;
  }

  // QUESTION: for some reason we don't need the -1 here?
  config_file_line[config_file_line_length] = '\0'; // get rid of the \n special character
  lhs = strsep(&config_file_line, "=");
  rhs = config_file_line;

  // TODO: should I use a hashmap better?
  if (strcmp(lhs, "prompt_color") == 0) {
    parsed_config_line.prompt_color = rhs;
    parsed_config_line.prompt_color[strlen(rhs)] = '\0';
  } else if (strcmp(lhs, "directory_color") == 0) {
    parsed_config_line.prompt_color = rhs;
    parsed_config_line.prompt_color[strlen(rhs)] = '\0';
  } else {
    parsed_config_line.prompt_color[0] = '\0';
    parsed_config_line.directory_color[0] = '\0';
  }

  return parsed_config_line;
}

// struct CommandLineConfig parse_config_line(char *line, size_t line_length) {
//   struct CommandLineConfig config_line = {NULL, 0, NULL};

//   // If the command line is empty (meaning it only has a line feed character and a null character)
//   // return empty command line input struct
//   if (line_length <= 1) {
//     return config_line;
//   }
  
//   char *lhs = strsep(&line, "=");
//   char *rhs = line;

//   if (strcmp(lhs, "directory_color") == 0) {
//     config_line.directory_color = malloc(sysconf(_SC_ARG_MAX));
//   }

//   // FF FF FF FF
//   if (strcmp(rhs, "prompt_color") == 0) {
//     config_line.prompt_color = malloc(4);
//   }

//   return config_line;
// }




int command_line_input_struct_array_length(CommandLineInput *struct_array) {
  int count = 0;
  while (struct_array->command != NULL) {
      struct_array++;
      count++;
  }
  return count;
}
