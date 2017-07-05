#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void check(const char* from, const char* to);


void check(const char* from, const char* to) {
  char current[1];
  size_t temp = read(0, current, 1);
    
  //temp must be greater than zero
  while (temp > 0) {
    size_t i;
    for (i = 0; i < strlen(from); i++) {
      if (current[0] == from[i]) {
	break;
      }
    }
    //making sure i is equal to current
    if (from[i] == current[0]) {
      current[0] = to[i];
      write(1,current,1);
    }
    temp = read(0, current, 1);
  }
}

int main(int argCount, const char* argument[]) {
  const char* from, *to;
    
  //if argument is more than 3
  if (argCount != 3) {
    fprintf(stderr, "Arguments should be 2, your argument is %d.\n", argCount);
    exit(1);
  }
    
  from = argument[1];
  to = argument[2];
    
  //check the size
  if (strlen(from) != strlen(to)){
    fprintf(stderr, "Two inputes are not the same size");
    exit(1);
  }
  // find duplicate
  for (size_t i = 0; i < strlen(from); i++) {
    for (size_t j = i + 1; j < strlen(from); j++) {
      if (from[i] == from[j]) {
	fprintf(stderr, "%s is dublicate", from);
	exit(1);
      }
    }
  }
    
  check(from, to);
  return 0;
}






