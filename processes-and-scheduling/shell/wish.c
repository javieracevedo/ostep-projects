#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "built_in_commands.h"
#include "system_commands.h"
#include "error_handling.h"

char *search_path = NULL;
size_t path_buffer_size = 20;

// Built In Commands Names
extern char *EXIT_COMMAND;
extern char *CD_COMMAND;
extern char *PATH_COMMAND;

int main(int argc, char *argv[]) {

  add_path_entry(&search_path, "/bin", &path_buffer_size);

  if (argc > 2) {
    fprintf(stderr, "usage: wish <batch.txt> or wish\n");
    free(search_path);
    exit(EXIT_FAILURE);
  }

  char *command_line = NULL;
  size_t command_line_buf_size = 100;
  struct CommandLineInput* commands;
  
  char current_wd_path[256];
  
  system("clear");
  while (1) {
    printf("%s >> ", getcwd(current_wd_path, 256));

    size_t nread = getline(&command_line, &command_line_buf_size, stdin);
    // TODO: maybe just pass the command_line and make the parse function handle empty strings. 
    commands = parse_command_line(command_line, nread);

    // TODO: check when there are no commands present (return with empty line)

    // TODO: We could have a single module called "commands" that handles both system calls to execute system commands and
    // built in commands. So we can execute built-in commands in parallel, together with system commands.
    if (strcmp(commands[0].command, CD_COMMAND) == 0 || strcmp(commands[0].command, PATH_COMMAND) == 0) {
        int return_code = handle_built_in_command(commands[0].command, commands[0].argc, commands[0].argv);
        print_error(return_code);
    } else if (strcmp( commands[0].command, EXIT_COMMAND) == 0) { 
      // TODO: handle ctrl+c and ctrl+d
      // TODO: is there a way to always ensure we exit trough here (or a single place), so we can free
      // everything we need to free and avoid memory leaks?
      if (commands[0].argc <= 1) {
        free(command_line);
        free(commands[0].argv);
        free(search_path);
        exit(EXIT_FAILURE);
      }

      print_error(-1);
    } else {
      int commands_count = command_line_input_struct_array_length(commands);
      execute_commands(commands, commands_count); 
    }
    
    free(commands[0].argv);
  }
}
