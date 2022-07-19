#include "minunit.h"
#include <stdio.h>


int tests_run = 0;

char *test_one_plus_one(void)
{ 
  MU_ASSERT("test 1+1", 1 == 1+1);
  return 0;
}

char *test_suite(void)
{
    MU_RUN_TEST(test_one_plus_one);
    return 0;
}

int main(int ac, char **av)
{
  char *result = test_suite();

  printf("number of tests run: %d\n", tests_run);
  if (result) printf("FAIL: %s\n", result);
  return 0 != result;
}