#include <stdio.h>

int main(int argc, char *argv[]) {
  if(argc == 1) {
    // Launch interface
    printf("Should be the interface here");
  } else {
    printf("test: %s", argv[0]);
  }
  return 0;
}