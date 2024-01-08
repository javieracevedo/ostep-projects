#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "built_in_commands.h"
#include "system_commands.h"
#include "error_handling.h"
#include "config.h"
#include "utils.h"
#include "cli_parser.h"


char *search_path = NULL;
size_t path_buffer_size = 20;

// Built In Commands Names
extern char *EXIT_COMMAND;
extern char *CD_COMMAND;
extern char *PATH_COMMAND;


void set_directory_path_color(char **config) {
  char *directory_color = find_config_value(&config, "directory_color", 6);
  print_directory_array(directory_color);
}

void set_prompt_symbol_color(char **config) {
  char *prompt_color = find_config_value(&config, "prompt_color", 6);
}

char *find_config_value(char **config, char *key, int length) {
  if (config == NULL) return NULL;

  for (int i=0; i<length; i++) {
    if (strcasecmp(key, config[i]) == 0) {
      return config[i+1];
    }
  }

  return NULL;
} 

// PARSE INTO AN ARRAY OF STRINGS
char **parse_config_into_array(FILE* file) {
  if (file == NULL) {
    return NULL;
  }

  char config_items_buffer_size = 100;
  char **config = calloc(config_items_buffer_size, sizeof(char *));

  size_t n;
  int nread;
  char *line_ptr = NULL;
  // QUESTION: what is size_t?

  int count = 0;
  while ((nread = getline(&line_ptr, &n, file)) != -1) {
    // QUESTION: does strdup copy the null terminator?
    // I think we could use strndup, maybe it doesn't use strlen, since we pass N
    // Maybe use on ourn impl, and compare execution times?
    char *line_ptr_dup = strdup(line_ptr);
    char *lhs = strsep(&line_ptr_dup, "=");
    // TODO: get rid of the \n character;
    char *rhs = line_ptr_dup;

    // QUESTION: will this fail if the configure items buffer size is not even?
    // I think it will.
    if (count >= config_items_buffer_size) {
      config_items_buffer_size = config_items_buffer_size * 2;
      if((*config = realloc(*config, config_items_buffer_size * sizeof(char *))) == NULL) {
        // Should we set an error or something here? to be printed with perror
        return NULL;
      }
    } 

    config[count] = lhs;
    config[count + 1] = rhs;
    count += 2;
  }
  config[count] = '\0';

  return config;
}

// PARSE INTO STRUCT
struct Config parse_config_file(FILE* file) {
  // QUESTION: This vs { NULL }, is there any difference
  struct Config config = {NULL};
  if (file == NULL) {
    return config;
  }

  int nread;
  char *line_ptr = NULL;
  size_t buffer_size = 0;

  while ((nread = getline(&line_ptr, &buffer_size, file)) != -1) {
    // QUESTION: does strdup copy the null terminator?
    // I think we could use strndup, maybe it doesn't use strlen, since we pass N
    // Maybe use on ourn impl, and compare execution times?
    char *line_ptr_dup = strdup(line_ptr);
    char *lhs = strsep(&line_ptr_dup, "=");
    char *rhs = line_ptr_dup;

    if (strcasecmp(lhs, "PROMPT_COLOR") == 0) {
      config.PROMPT_COLOR = rhs;
    } else if (strcasecmp(lhs, "DIRECTORY_COLOR") == 0) {
      config.DIRECTORY_COLOR = rhs;
    }
  }

  free(line_ptr);

  return config;
}

int main(int argc, char *argv[]) {
  // char *should_fail = malloc(2);
  // should_fail[0] = 'h'; // "h"
  // should_fail[1] = '\0'; // "h"

  // printf("%ld\n", strlen(should_fail));

  // free(should_fail);



  // char *test = "Hello World";
  // char *dup_test = __strdup(test);

  // printf("%c\n", dup_test);




  // TODO: This paths should be read from the shell config file, then iterate over all of them and call add path entry 
  // add_path_entry(&search_path, "/bin", &path_buffer_size);
  // add_path_entry(&search_path, "/opt/local/bin", &path_buffer_size);
  // add_path_entry(&search_path, "/opt/homebrew/bin", &path_buffer_size);
  // add_path_entry(&search_path, "/Users/Javier/.nvm/versions/node/v12.14.1/bin", &path_buffer_size);
  // add_path_entry(&search_path, "/usr/bin", &path_buffer_size);

  // if (argc > 2) {
  //   fprintf(stderr, "usage: wish <batch.txt> or wish\n");
  //   free(search_path);
  //   exit(EXIT_FAILURE);
  // }

  // struct CommandLineInput* commands;
  FILE *config_file;
  if ((config_file = fopen("./config-file.wsh", "r")) == NULL) {
    fprintf(stderr, "wish: could not read configuration file\n");
    exit(EXIT_FAILURE);
  }

  // if (argc == 2) {
  //   FILE *file;
  //   if ((file = fopen(argv[1], "r")) == NULL) {
  //     fprintf(stderr, "wish: cannot read file\n");
  //     exit(EXIT_FAILURE);
  //   }
  //   size_t buffer_size = 256;
  //   char *buffer = NULL;
  //   ssize_t nread;
  
  //   while ((nread = getline(&buffer, &buffer_size, file)) != -1) {
  //     commands =  parse_command_line(buffer, nread);
  //     int commands_count = command_line_input_struct_array_length(commands);
      
  //     for (int i = 0; i < commands_count; i++) {
  //       if (strcmp(commands[i].command, CD_COMMAND) == 0) {
  //         handle_built_in_command(commands[i].command, commands[i].argc, commands[i].argv);
  //       } else if (strcmp(commands[i].command, PATH_COMMAND) == 0) {
  //         handle_built_in_command(commands[i].command, commands[i].argc, commands[i].argv);
  //       } else {
  //         execute_commands(commands, commands_count);
  //       }
  //     }
  //   }

  //   exit(EXIT_SUCCESS);
  // }

  // char *command_line = NULL;
  // size_t command_line_buf_size = 100;
  
  // system("clear");

  char **config = parse_config_into_array(config_file);

  // printf("%p\n", config_file);
  // struct Config parsed_config_file = parse_config_file(config_file);

  // printf("%s\n", parsed_config_file.DIRECTORY_COLOR);
  // printf("%s\n", parsed_config_file.PROMPT_COLOR);


  // while (1) {
  //   // print_directory(parsed_config_file);
  //   // print_prompt(parsed_config_file);

  //   size_t nread = getline(&command_line, &command_line_buf_size, stdin);
  //   if (command_line[0] != '\n') {
  //     commands = parse_command_line(command_line, nread);

  //     if (strcmp(commands[0].command, CD_COMMAND) == 0 || strcmp(commands[0].command, PATH_COMMAND) == 0) {
  //       int return_code = handle_built_in_command(commands[0].command, commands[0].argc, commands[0].argv);
  //       print_error(return_code);
  //     } else if (strcmp( commands[0].command, EXIT_COMMAND) == 0) {
  //       if (commands[0].argc <= 1) {
  //         free(command_line);
  //         free(commands[0].argv);
  //         free(search_path);
  //         exit(EXIT_FAILURE);
  //       }

  //       print_error(-1);
  //     } else {
  //       int commands_count = command_line_input_struct_array_length(commands);
  //       execute_commands(commands, commands_count); 
  //     }
      
  //     free(commands[0].argv);
  //   }
  // }
}


//  Resources   //
// 
//  https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
//  https://www.linuxjournal.com/article/8603
//