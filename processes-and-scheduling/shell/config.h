#include <stdio.h>

// TODO: read more about structs?
typedef struct Config {
  char *PROMPT_COLOR;
  char *DIRECTORY_COLOR;
} Config;

struct Config parse_config_file(FILE *file);
