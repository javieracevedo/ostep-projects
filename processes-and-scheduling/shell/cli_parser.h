#include <stddef.h>

#ifndef CLI_PARSER_H
#define CLI_PARSER_H

// QUESTION: Would it be worth it to have a types file? 
typedef struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
  char *redirectFileName;
} CommandLineInput;

typedef struct CommandLineConfig {
  char *directory_color;
  char *prompt_color;
} CommandLineConfig;

#endif


char* trim_spaces(const char *string, size_t string_length);
struct CommandLineInput* parse_command_line(char *command_line, size_t command_line_length);
struct CommandLineInput parse_command(char *command_line, size_t command_line_length);
struct CommandLineConfig parse_config_file_line(char *config_file_line, size_t config_file_line_length);
struct CommandLineConfig parse_config_line(char *line, size_t line_length);
int command_line_input_struct_array_length(struct CommandLineInput *struct_array);

