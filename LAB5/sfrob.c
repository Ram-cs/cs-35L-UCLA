#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char decript(const char ch);
int cmp(const void* int1, const void* int2);
void errorCheck();
void memoryErrorAllocation(char* ch);
void errorAM(char* ch);
void putcharOutput(int wordsIterator, char** arryWord);
void freeMemory(int wordsIterator, char** arryWord);


char decript(const char ch) {
  return ch ^42;
}


//compare two unfrobnicated words
int frobcmp(char const* a, char const* b) {
  while(1) {
    if (*a == ' ' && *b == ' ')
      return 0; //if equal return 0
    else if (*b == ' ' || (decript(*a) > decript(*b)))
      return 1;
    else if (*a == ' ' || (decript(*a) < decript(*b)))
      return -1;
    a++;
    b++;
  }
}

int cmp(const void* int1, const void* int2) {
  return frobcmp(*((const char**) int1), *((const char**) int2));
}

//check for file error
void errorCheck() {
  if (ferror(stdin)) {
    fprintf(stderr, "Error reading file: ");
    exit(1);
  }
}

//memory error
void memoryErrorAllocation(char* ch) {
  free(ch);
  fprintf(stderr, "Error in Memory Allocation!");
  exit(1);
}


void errorAM(char* ch) {
  free(ch);
  fprintf(stderr, "Error Allocation Memory!");
  exit(1);
}

//output the word to STDOUT using putchar
void putcharOutput(int wordsIterator, char** arryWord) {
  for(size_t i = 0; i < wordsIterator; i++) {
    for(size_t j = 0; ;j++) {
      //Check error when EOF
      if(putchar(arryWord[i][j]) == EOF) {
	fprintf(stderr,"Error while writing!");
	exit(1);
      }
      if(arryWord[i][j] == ' ') {
	break;
      }
    }
  }
}

//free memory
void freeMemory(int wordsIterator, char** arryWord) {
  for(size_t i = 0; i < wordsIterator; i++) {
    free(arryWord[i]);
  }
  free(arryWord);
  exit(0);
}

int main(void) {
  char* holdWord = (char*)malloc(sizeof(char)); //holds one words at a time
  char** arryWord = (char**)malloc(sizeof(char*));//pointers to hold words
    
  char current[1], next;
  size_t temp = read(0, current, 1);
  errorCheck();
    
  next = getchar();
  errorCheck();
    
  next = getchar();
  errorCheck();
    
  int charIterator = 0;
  int wordsIterator = 0;
    
  while (temp > 0) { //read file untill end of word
    holdWord[charIterator] = current[0];
    char* tmp = realloc(holdWord, (charIterator+2)* sizeof(char));
        
    if (tmp != NULL) {
      holdWord = tmp; //word is equal to the reallocated memory
    } else { //error handling for memory
      errorAM(holdWord);
    }
    if (current[0] == ' ') { //when hit the end of the word
      arryWord[wordsIterator] = holdWord;
      char** newOne = realloc(arryWord, (wordsIterator+2)*sizeof(char*)); //adding letter to word
      if (newOne == NULL) {
	memoryErrorAllocation(holdWord);
      } else {
	arryWord = newOne;
	wordsIterator++;
	holdWord = NULL;
	holdWord = (char*)malloc(sizeof(char));
	charIterator = -1; //after summed later bring back to -1
      }
    }
        
    if (next == EOF && current[0] == ' ') {
      break;
    }
        
    else if (current[0] == ' ' && next == ' ') { //when extra space
      while(current[0] == ' ') {
	current[0] = getchar();
	errorCheck();
      }
            
      next = getchar();
      errorCheck();
      charIterator++;
      continue;
    }
        
    else if (next == EOF) { //when not at the end of the line
      current[0] = ' ';
      charIterator++;
      continue;
    }
    current[0] = next; //when current is next
    next = getchar();
        
    errorCheck();
    charIterator++;
        
  }
    
  //sorting the frobnicated words
  qsort(arryWord, wordsIterator, sizeof(char*), cmp);
    
  //output the word to STDOUT using putchar
  putcharOutput(wordsIterator, arryWord);
    
  //free the moemory
  freeMemory(wordsIterator, arryWord);
}


        


