#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct CommandLineInput {
  char *command;
  int argc;
  char **argv;
} CommandLineInput;


// CommandLineInput *parse_command_line(char *command_line, size_t nread) {
//   // basically, if command line is empty (meaning it only has a line feed character and a null character)
//   // return empty command line input struct
//   if (nread <= 1) {
//     return NULL;
//   }

//   struct CommandLineInput *command_line_input;
//   if ((command_line_input = malloc(sizeof(struct CommandLineInput))) == NULL) {
//     fprintf(stderr, "creation of CommandLineInput struct failed\n");
//   }

//   command_line[nread - 1] = '\0'; // get rid of the \n special character

//   int idx = 0;
//   // TODO: test if we need to do sizeof(char *) * the amount of strings I'll hold
//   command_line_input->argv = malloc(sizeof(char *));
//   while (command_line != NULL) {
//     char *token = strsep(&command_line, " ");
//     command_line_input->argv[idx] = malloc(sizeof(char *));
//     if (command_line_input->argv[idx] == NULL) {
//       // TODO: should we avoid printing the error and exiting here?
//       // should we handle this like C functions handle this, by maybe returning NULL and setting errno
//       fprintf(stderr, "malloc failed while parsing token: %s\n", token);
//       exit(EXIT_FAILURE);
//     }
//     command_line_input->argv[idx] = token;
//     idx++;
//   }
//   command_line_input->argc = idx;
//   command_line_input->command = command_line_input->argv[0];

//   return command_line_input;
// }

// Built In Commands Names

// char *EXIT_COMMAND = "exit";
// char *CD_COMMAND = "cd";
// char *PATH_COMMAND = "path";
char **path = NULL;
int path_length = 1;


//void handle_built_in_command(char *command, int argc, char **argv) {
//   if (strcmp(command, EXIT_COMMAND) == 0) {
//     if (argc > 1) {
//       fprintf(stderr, "exit: too many arguments\n");
//     }
//     exit(EXIT_FAILURE);
//   } else if (strcmp(command, CD_COMMAND) == 0) {
//     if (argc > 2) {
//       fprintf(stderr, "cd: too many arguments\n");
//     } else if (chdir(argv[1]) == -1) {
//       fprintf(stderr, "An error has ocurred\n");
//     }
//   } else if (strcmp(command, PATH_COMMAND) == 0) {
//     // TODO: we probably will need to check if resizing path is necessary
//     // TODO: check for memory issues
//     // TODO: maybe create a function  set_path.
//     for (int i=1; i<argc; i++) {
//       path[i] = malloc(sizeof(char *));
//       path[i] = argv[i];
//     }

//     for (int j=0; j<argc; j++) {
//       printf("%s\n", path[j]);
//     }
//   }
// }

// TODO: is there a better way to do this?
int get_array_len(char **array) {
  int current_idx = 0;
  char *current_item = array[current_idx];
  while (current_item != NULL) {
    current_item = array[current_idx];
    if (current_item) current_idx++;
  }
  return current_idx;
}

int str_array_length(char **array) {
  if (!array) return 0;

  int current_element_idx = 0;
  char *current_element;
  while ((current_element = array[current_element_idx]) != NULL) {
    current_element_idx++;
  }

  return current_element_idx;
}

void str_array_push(char **array, char *new_element, int *buffer_size) {
  int array_length = str_array_length(array); // We could avoid this by somehow keeping track of the elements added to the array each time.
  if (array_length >= *buffer_size - 1) {
    // TODO: realloc array, do we need to derreference array here or not?
    *buffer_size = *buffer_size * 2;
    if ((array = realloc(array, *buffer_size * sizeof(char *))) == NULL) {
      fprintf(stderr, "realloc failed");
      exit(EXIT_FAILURE);
    }
  }
  array[array_length] = new_element;
}

//void add_path_entry(char **path, char *new_entry, int *buffer_size) {
  // TODO
//  if (!path) {
//    if ((path = calloc(path_length + 1, sizeof(char *))) == NULL) {
//      fprintf(stderr, "calloc failed");
//      exit(EXIT_FAILURE);
//    }
//  }
//}

void add_path_entry(char *entry, int path_len) {
  if (!path) {
    // Consider locating the + 1 somewhere else. Place it where it retter indicates the     // need of an extra null character.        
    path = calloc(path_length + 1, sizeof(char *));
    if (!path) {
      fprintf(stderr, "calloc failed");
      exit(EXIT_FAILURE);
    }
    //if ((path = calloc(path_length + 1, sizeof(char *))) == NULL) {
	//  fprintf(stderr, "calloc failed");
    //  exit(EXIT_FAILURE);
    //}
  }

  //int path_len = get_array_len(path);
  if (path_len >= path_length) {
    char **new_path;
    if ((new_path = realloc(path, ((path_length * 2) + 1) * sizeof(char *))) == NULL) {
      fprintf(stderr, "realloc failed");
      exit(EXIT_FAILURE);
    }
    path = new_path;
    path_length = (path_length * 2) + 1;
  }
  // TODO: also, should we check if re-alloc is needed?
  path[path_len] = entry;
}

// void handle_system_command(char *command) {
//   if (path[0] != "\0") { // TODO: consider removing this
//     char *path_copy = strdup(path);

//     char *token;
//     char *command_path = "\0";

//     while (path_copy != NULL && command_path[0] == '\0') {
//       token = strsep(&path_copy, " ");

//       char *possible_command_path = strdup(token);
//       strcat(possible_command_path, "/");
//       strcat(possible_command_path, command);

//       if (access(possible_command_path, X_OK) == 0) {
//         command_path = strdup(possible_command_path);
//       }
//     }

//     if (command_path[0] == '\0') {
//       fprintf(stderr, "wish: could not find %s command\n", command);
//     } else {
//       char *newargv[] = { };
//       // char *newenviron[] = { NULL };

//       int error;
//       if ((error = execv(command_path, newargv)) != 0) {
//         perror("wish: an error has ocurred");
//       }
//     }
//   } else {
//     printf("wish: path is not set");
//   }
// }

// int is_built_in_command(char *command) {
//   return strcmp(command, EXIT_COMMAND) == 0 || strcmp(command, CD_COMMAND) == 0 || strcmp(command, PATH_COMMAND) == 0;
// }

int main(int argc, char *argv[]) {
  //int path_len = get_array_len(path);
  // TODO: modify add_path_entry so it takes a char** path, int** buffer_size, char* en  // try
  // TODO: consider getting rid of current path len, and use the NULL at the end to kno
  // if you need to resize?
  char *item = "item";
  char **str_test = calloc(100, sizeof(char *));
  int buffer_size = 2;
  str_test[0] = "1";
  str_array_push(str_test, "2", &buffer_size);
  str_array_push(str_test, "3", &buffer_size);
  //void str_array_push(char **array, char *new_element, int *buffer_size) {
 
  

  //str_test[1] = "item 2";
  //str_test[2] = "item 3";
  //str_test[3] = "item 4";
  //str_test[4] = "item 5";
  //str_test[5] = "item 6";
  printf("str len: %d", str_array_length(str_test));

   free(str_test);
  //add_path_entry("2", 0);
  //add_path_entry("3", 1);
  //add_path_entry("4", 2);
  //add_path_entry("5", 3);
  //add_path_entry("6", 4);
  //add_path_entry("7", 5);
  //add_path_entry("8", 6);
  //add_path_entry("9", 7);

  // for (int i=0; i<get_array_len(path); i++) {
  //   printf("%s\n", path[i]);
  // }

  //free(path);
  // free_path_entries();

  // if (argc > 2) {
  //   fprintf(stderr, "usage: wish <batch.txt> or wish\n");
  //   exit(EXIT_FAILURE);
  // }

  // char *command_line = NULL;
  // size_t command_line_buf_size = 0;
  
  // int running = 1;
  // while (running) {
  //   system("pwd");

  //   size_t nread = getline(&command_line, &command_line_buf_size, stdin);
  //   CommandLineInput *command_line_input = parse_command_line(command_line, nread);

  //   if (command_line_input != NULL) {
  //     if (is_built_in_command(command_line_input->command)) {
  //       handle_built_in_command(command_line_input->command, command_line_input->argc, command_line_input->argv);
  //     } else {
  //       // TODO: handle system command
  //       // handle_system_command(command_line_input->command);
  //     }
  //   }
}

