#include <stddef.h>

typedef struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
  char *redirectFileName;
} CommandLineInput;

char* trim_spaces(const char *string, size_t string_length);

struct CommandLineInput* parse_command_line(char *command_line, size_t command_line_length);
struct CommandLineInput parse_command(char *command_line, size_t command_line_length);

int command_line_input_struct_array_length(struct CommandLineInput *struct_array);