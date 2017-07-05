#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



int f_option = 0;

char decript(const char ch) {
  return ch ^42;
}

int frobcmp(char const *a, char const *b)
{
  if(f_option == 0) {
    for(;; a++, b++) {
      if (*a == ' ' && *b == ' ')
	return 0; //if equal return 0
      else if (*b == ' ' || (decript(*a) > decript(*b)))
	return 1;
      else if (*a == ' ' || (decript(*a) < decript(*b)))
	return -1;
    }
  } else {
    for(;; a++, b++) {
      //UCHAR_MAX check if a and b is valid character
      if(*a <= UCHAR_MAX && *b <= UCHAR_MAX) {
	if(*a == ' ' && *b == ' ') { return 0; }
	else if(*a == ' ' || (toupper(*a^42) < toupper(*b^42))) { return -1; }
	else if(*b == ' ' || (toupper(*a^42) > toupper(*b^42))) { return 1; }
      }
            
      if(*a <= UCHAR_MAX && *b > UCHAR_MAX) {
	if(*a == ' ' && *b == ' ') { return 0; }
	else if(*a == ' ' || (toupper(*a^42) < (*b^42))) { return -1; }
	else if(*b == ' ' || (toupper(*a^42) > (*b^42))) { return 1; }
      }
            
      if(*a > UCHAR_MAX && *b <= UCHAR_MAX) {
	if(*a == ' ' && *b == ' ') { return 0; }
	else if(*a == ' ' || ((*a^42) < toupper(*b^42))) { return -1; }
	else if(*b == ' ' || ((*a^42) > toupper(*b^42))) { return 1; }
      }
    }
  }
    
}

int cmp(const void* int1, const void* int2)
{
  //cast pointer to pointer
  return frobcmp(*((const char**) int1), *((const char**) int2));
}

void readErr(ssize_t state)
{
  if(state < 0)
    {
      fprintf(stderr, "Error reading file: ");
      exit(1);
    }
}

int main(int argc, char* argv[]) {
    
  //Check for -f option
  if(argc >= 2 && strcmp(argv[1], "-f") == 0) {
    //f-optin is set true
    f_option = 1;
  }
    
    
  struct stat files;
  if(fstat(0,&files) < 0)
    {
      fprintf(stderr, "fstate error!");
      exit(1);
    }
  char **holdWord;
  char *arryOfFile;
  size_t holdWordIterator = 0;
  if(S_ISREG(files.st_mode))
    {
      arryOfFile = (char*)malloc(files.st_size * sizeof(char));
      int pntCnt = 0;
      ssize_t state = read(0, arryOfFile, files.st_size);
      int count = 1;
      if(state > 0) //No error reading
        {
	  for(size_t i = 0; i < files.st_size; i+=count)
            {
	      count = 1;
	      if(i == files.st_size - 1) //space has been set at the end
                {
		  arryOfFile[i] = ' ';
                }
	      if(arryOfFile[i] == ' ')
                {
		  for(size_t j = i; arryOfFile[j] != ' '; j++)
                    {
		      count++;
                    }
		  pntCnt++;
                }
            }
        }
        
      holdWord = (char**)malloc(pntCnt * sizeof(char*));
      int flag = 0;
      for(size_t i = 0; i < files.st_size; i++)
        {
	  if(flag == 0 && arryOfFile[i] != ' ')
            {
	      holdWord[holdWordIterator] = &arryOfFile[i];
	      holdWordIterator++;
	      flag = 1;
            }
	  else if(flag == 1 && arryOfFile[i] == ' ')
            {
	      flag = 0;
            }
        }
    }
  else
    {
      holdWord = (char**)malloc(sizeof(char*));
    }
    
    
  char* word; //delimited by spaces
  word = (char*)malloc(sizeof(char));
  //curr and next act as current and next iterators to use for noting
  //EOF and auto adding spaces at the end of files
  char curr[1];
  ssize_t currState = read(0, curr, 1);
  readErr(currState);
  char next[1];
  ssize_t nextState = read(0, next, 1);
  readErr(nextState);
  int letterIterator = 0;
    
  while(currState > 0) {
    word[letterIterator] = curr[0]; //letter is adding to the word
    //realocate memeory for the new word
    char* temp = realloc(word, (letterIterator+2)*sizeof(char));
    if(temp != NULL)
      {
	//word is equal to reallocated
	word = temp;
      }
    else //Error allocation memeory
      {
	free(word);
	fprintf(stderr, "Error Allocation Memory has be encountered!");
	exit(1);
      }
        
    if(curr[0] == ' ') //when hit the end of the word
      {
	holdWord[holdWordIterator] = word;
	char** anotherOne = realloc(holdWord, (holdWordIterator+2)*sizeof(char*));
	if(anotherOne != NULL)
	  {
	    //word is equal to reallocated memeory
	    holdWord = anotherOne;
	    holdWordIterator++;
	    //Setting word to equal
	    word = NULL;
	    word = (char*)malloc(sizeof(char));
	    letterIterator = -1; //-1 to bring back to 0 when summed later
	  }
	else //Error allocation memeory
	  {
	    free(holdWord);
	    fprintf(stderr, "Error Allocation Memory occur!");
	    exit(1);
	  }
      }
    if(nextState == 0 && curr[0] == ' ')
      {
	break;
      }
    else if (curr[0] == ' ' && next[0] == ' ') //If there is space then ignore it
      {
	while(curr[0] == ' ') {
	  currState = read(0,curr,1);
	  readErr(currState);
	}
	nextState = read(0,next,1);
	readErr(nextState);
	letterIterator++;
	continue;
      }
    else if(nextState == 0) //adding the space at the end
      {
	curr[0] = ' ';
	letterIterator++;
	continue;
      }
    //get the next character by incremeting our lette center
    curr[0] = next[0];
    nextState = read(0, next, 1);
    readErr(nextState);
    letterIterator++;
  }
  //sorting the frobnicated holdWord
  qsort(holdWord, holdWordIterator, sizeof(char*), cmp);
  //Outputting the word
  for(size_t i = 0; i < holdWordIterator; i++) {
    long holdWordize = 0;
    for(size_t j = 0; ;j++) {
      holdWordize++;
      if(holdWord[i][j] == ' ') {
	break;
      }
    }
    if(write(1,holdWord[i], holdWordize) == 0) {
      fprintf(stderr, "Error occur while writing!");
      exit(1);
    }
  }
  free(holdWord);
  exit(0);
}
