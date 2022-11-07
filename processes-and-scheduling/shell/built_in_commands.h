int add_path_entry(char **search_path, char *new_entry, size_t *buffer_size);
int handle_exit_command(int argc);
int handle_cd_command(int argc, char **argv);
int handle_path_command(int argc, char **argv);
int handle_built_in_command(char *command, int argc, char **argv);
