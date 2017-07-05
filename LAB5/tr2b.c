#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void check(const char* from, const char* to);


void check(const char* from, const char* to) {
  char current = getchar();
    
  //when current is not the End of the Line
  while (current != EOF) {
    size_t i;
    for (i = 0; i < strlen(from); i++) {
      if (current == from[i]) {
	break;
      }
    }
    //check when current is from
    if (current == from[i]) {
      putchar(to[i]);
    } else {
      //if current is not from then currrent is putchar
      putchar(current);
    }
        
    current = getchar();
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
    
  //check the size of the file
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






