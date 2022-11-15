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
  add_path_entry(&search_path, "/opt/local/bin", &path_buffer_size);
  add_path_entry(&search_path, "/opt/homebrew/bin", &path_buffer_size);
  add_path_entry(&search_path, "/Users/Javier/.nvm/versions/node/v12.14.1/bin", &path_buffer_size);
  add_path_entry(&search_path, "/usr/bin", &path_buffer_size);

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
    if (command_line[0] != '\n') {
      commands = parse_command_line(command_line, nread);

      if (strcmp(commands[0].command, CD_COMMAND) == 0 || strcmp(commands[0].command, PATH_COMMAND) == 0) {
          int return_code = handle_built_in_command(commands[0].command, commands[0].argc, commands[0].argv);
          print_error(return_code);
      } else if (strcmp( commands[0].command, EXIT_COMMAND) == 0) {
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
}


// BUGS
  // #1 - I think this one was fix together with another bug. Will leave here just in case.
    // wish.out(63472,0x1efebe500) malloc: Incorrect checksum for freed object 0x121e068b8: probably modified after being freed.
    // Corrupt value: 0x69622f312e34312e
    // wish.out(63472,0x1efebe500) malloc: *** set a breakpoint in malloc_error_break to debug
