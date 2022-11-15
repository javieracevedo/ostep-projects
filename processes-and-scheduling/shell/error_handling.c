#include <unistd.h>
#include "error_handling.h"

void print_error(int return_code) {
  if (return_code < 0) {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, 30);
  }
}