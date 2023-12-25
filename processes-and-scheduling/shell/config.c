#include "config.h"
#include <errno.h>


struct Config parse_config_file(FILE *file) {
  size_t buffer_size = 0;
  char *buffer = NULL;
  ssize_t nread;
  struct Config config = {};

  while ((nread = getline(&buffer, &buffer_size, file)) != -1) {
    char *lhs = strsep(&buffer, "=");
    char *rhs = buffer;

    if (strcmp(lhs, "prompt_color") == 0) {
      if ((config.PROMPT_COLOR=strdup(rhs)) == NULL) {
        print_error(errno);
      }
    } else if (strcmp(lhs, "directory_color") == 0) {
      if ((config.DIRECTORY_COLOR=strdup(rhs)) == NULL) {
        print_error(errno);
      }
    }
    buffer = NULL;
  }

  free(buffer);
  return config;
}
