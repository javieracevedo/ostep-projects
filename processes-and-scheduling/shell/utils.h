void set_cli_color_red();
void set_cli_color_green();
void set_cli_color_blue();
void set_cli_color_white();
void set_cli_color_black();
void reset_cli_color();

char* get_last_dir_name(char *cwd);
void print_directory(struct Config cli_config);
void print_prompt(struct Config cli_config);