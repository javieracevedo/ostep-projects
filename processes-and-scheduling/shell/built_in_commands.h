int add_path_entry(char **search_path, char *new_entry, size_t *buffer_size);
void handle_exit_command(int argc);
void handle_cd_command(int argc, char **argv);
void handle_path_command(int argc, char **argv);
void handle_built_in_command(char *command, int argc, char **argv);
