#include <unistd.h>
#include "config.h"

void set_cli_color_red() {
  printf("\033[0;31m");
}

void set_cli_color_green() {
  printf("\033[0;32m");
}

void set_cli_color_blue() {
  printf("\033[0;34m");
}

// TODO: check why this doesn't work?
void set_cli_color_white() {
  printf("\033[0;37m");
}

void set_cli_color_black() {
  printf("\033[0;30m");
}

void reset_cli_color() {
  printf("\033[0m");
}

char* get_last_dir_name(char *cwd) {
  char *separator = "/";
  char *token = strsep(&cwd, separator);
  char **tokens = malloc(sizeof(char*) * 20);

  int idx = 0;
  while (token != NULL) {
    token = strsep(&cwd, separator);
    tokens[idx] = token;
    if (token) idx++;
  }

  if (idx > 0) return tokens[idx - 1];
  return NULL;
}

void print_directory(struct Config cli_config) {
  char current_wd_path[256];
  char *cwd = getcwd(current_wd_path, 256);
  char *last_dir = get_last_dir_name(cwd);

  if (cli_config.DIRECTORY_COLOR == NULL) {
    printf("%s ", last_dir);
    return;
  }

  if (strcasecmp(cli_config.DIRECTORY_COLOR, "#00FF00\n") == 0) {
    set_cli_color_green();
  } else if (strcasecmp(cli_config.DIRECTORY_COLOR, "#0000FF\n") == 0) {
    set_cli_color_blue();
  } else if (strcasecmp(cli_config.DIRECTORY_COLOR, "#FFFFFF\n") == 0) {
    set_cli_color_white();
  } else if (strcasecmp(cli_config.DIRECTORY_COLOR, "#FF0000\n") == 0) {
    set_cli_color_red();
  }

  printf("%s ", last_dir);
  reset_cli_color();
}

void print_directory_array(char *directory_color) {
  char current_wd_path[256];
  char *cwd = getcwd(current_wd_path, 256);
  char *last_dir = get_last_dir_name(cwd);

  if (directory_color == NULL) {
    printf("%s ", last_dir);
    return;
  }

  if (strcasecmp(directory_color, "#00FF00\n") == 0) {
    set_cli_color_green();
  } else if (strcasecmp(directory_color, "#0000FF\n") == 0) {
    set_cli_color_blue();
  } else if (strcasecmp(directory_color, "#FFFFFF\n") == 0) {
    set_cli_color_white();
  } else if (strcasecmp(directory_color, "#FF0000\n") == 0) {
    set_cli_color_red();
  }

  printf("%s ", last_dir);
  reset_cli_color();
}

void print_prompt(struct Config cli_config) {
  if (cli_config.PROMPT_COLOR == NULL) {
    printf(">> ");
    return;
  }
  
  if (strcasecmp(cli_config.PROMPT_COLOR, "#00FF00\n") == 0) {
    set_cli_color_green();
  } else if (strcasecmp(cli_config.PROMPT_COLOR, "#0000FF\n") == 0) {
    set_cli_color_blue();
  } else if (strcasecmp(cli_config.PROMPT_COLOR, "#FFFFFF\n") == 0) {
    set_cli_color_white();
  } else if (strcasecmp(cli_config.PROMPT_COLOR, "#FF0000\n") == 0) {
    set_cli_color_red();
  } else {
    reset_cli_color();
  }

  printf(">> ");
  reset_cli_color();
}

void print_prompt_array(char *prompt_array) {
  if (prompt_array == NULL) {
    printf(">> ");
    return;
  }
  
  if (strcasecmp(prompt_array, "#00FF00\n") == 0) {
    set_cli_color_green();
  } else if (strcasecmp(prompt_array, "#0000FF\n") == 0) {
    set_cli_color_blue();
  } else if (strcasecmp(prompt_array, "#FFFFFF\n") == 0) {
    set_cli_color_white();
  } else if (strcasecmp(prompt_array, "#FF0000\n") == 0) {
    set_cli_color_red();
  } else {
    reset_cli_color();
  }

  printf(">> ");
  reset_cli_color();
}