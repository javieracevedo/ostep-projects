// QUESTION: do we need to include header files inside other header files?
#include "cli_parser.h"

void handle_system_command(char *command, char **argv, char *redirectFileName);
void execute_commands(CommandLineInput *commands, int length);
