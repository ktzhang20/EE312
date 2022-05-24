/*
 * Project1.cpp
 * 
 * Name: Ima Student
 * EE312 Spring 2016
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <string.h>
#include <ctype.h>

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

char * arr;
char * dict1;
char * saveptr;
int inDict(char dictionary[], char arr[], char dict1[]);

void getWord(char article[], int i);

void spellCheck(char article[], char dictionary[]) {

  char * art = article;
  int i = 0; int v = 0; int count = 0;
  while((arr = strtok_r(art, " ,.-'", &art))){
      if(strlen(arr) >= 2){
        if(inDict(dictionary, arr, dict1) == 0){
         printf("%s\n", arr);
        }
      }
  }



}


/*
What I think I have to do for inDict:
While loop ending at null terminator '\0'.
can't just do == for each character because capitals matter

*/

int inDict(char dictionary[], char arr[], char dict1[]){
  int v = 0; int i = 0;
  for(dict1 = strtok_r(dictionary, "\n", &saveptr);
    dict1 != NULL;
    dict1 = strtok_r(NULL, "\n", &saveptr)){
    v = 0;
    for(int x = 0; x < strlen(arr); x++){
      if(strlen(dict1) < strlen(arr)){
        v = 1;
        break;
      }
      if(tolower(dict1[i] != tolower(arr[x]))){
        v = 1;
        break;
      }
      i++;
    }
    if(v == 0)
      return 1;
  }
  return 0;
}




/*while(article[i] != '0'){
    if(article[i] == ' ' || article[i] == ',' || article[i] == '.' || article[i] == '\'' || article[i] == '\n'){
      printf("\n");
      v = 0;
      count = 0;
      i ++;
      continue;
    }
    if(v == 0){
        strtok;
        printf("%c", article[i]);
        count++;
        i++;
    }*/

    /*while(dict != NULL){
    v = 0;
    for(int x = 0; x < strlen(arr); x++){
      if(tolower(dict[i]) != tolower(arr[x])){
        v = 1;
        break;

      }
      i++;
    }
    if(v == 0)
      return 1;
    dict = strtok(NULL, "\n");
    
    
  }
  return 0;*/