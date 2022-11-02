#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// #include "cli_parser.h"
#include "built_in_commands.h"
#include "system_commands.h"
#include "array_lib.h"


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
  
  // system("clear")  ;
  while (1) {
    system("pwd");

    size_t nread = getline(&command_line, &command_line_buf_size, stdin);
    // TODO: maybe just pass the command_line and make the parse function handle empty strings. 
    commands = parse_command_line(command_line, nread);

    int commands_count = command_line_input_struct_array_length(commands);
    execute_commands(commands, commands_count);


  //   for (int i=0; i<=get_array_length(commands); i++) {
  //     if (strcmp(commands[i].command, CD_COMMAND) == 0 || strcmp(commands[i].command, PATH_COMMAND) == 0) {
  //       handle_built_in_command(commands[i].command, commands[i].argc, commands[i].argv);
  //     } else if (strcmp( commands[i].command, EXIT_COMMAND) == 0) { // TODO: handle ctrl+c and ctrl+d
  //       if (commands[i].argc <= 1) {
  //         free(command_line);
  //         free(commands[i].argv);
  //         free(search_path);
  //         exit(EXIT_FAILURE);
  //       }

  //       fprintf(stderr, "exit: too many arguments\n");
       
  //     } else {
  //       handle_system_command(commands[i].command, commands[i].argv, commands[i].redirectFileName);
  //     }

  //     free(commands[i].argv);
  //     // free(command_line_input);
  //   }
  }
}
