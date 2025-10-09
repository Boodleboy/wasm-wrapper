#include <stdio.h>

int
main(void) {
  FILE *fptr = fopen("file.txt", "w");
  printf("file opened maybe\n");
  return 0;
}
