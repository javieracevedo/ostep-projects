struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
  char *redirectFileName;
};

struct CommandLineInput parse_command_line(char *command_line, size_t command_line_length);