#include <stdio.h>
#include <testfile.h>

int main() {
  printf("about to run new func\n");

  test_lib_ext();
  top_ext_test();
  printf("done\n");
  return 0;
}
