#include <stddef.h>

typedef struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
  char *redirectFileName;
} CommandLineInput;

void trim_spaces(char **string);

struct CommandLineInput* parse_command_line(char *command_line, size_t command_line_length);
struct CommandLineInput parse_command(char *command_line, size_t command_line_length);

int command_line_input_struct_array_length(struct CommandLineInput *struct_array);