/* Daniel Eisterhold
 * dte130030
 * CS 3376.502
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse.h"

int yylex(void);
extern char* yytext;
int yyparse(void);

int main(int argc, char *argv[]) {
  //Get directory where the program was run
  char* programName = argv[0];

  //Check to see how the program was called
  if(strstr(programName,"scanner") != NULL) {
    //Output that the program was run in scanner mode
    printf("\nOperating in scan mode\n\n");
    
    //Flag to know when to exit the loop
    bool exit = false;

    //Loop until reached end of file
    while(!exit) {
      int value = yylex();
      
      switch(value) {
	case NAMETOKEN:
	  printf("yylex returned NAMETOKEN token (%s)\n", yytext);
	  break;
	case IDENTIFIERTOKEN:
	  printf("yylex returned IDENTIFIERTOKEN token (%s)\n", yytext);
          break;
	case NAME_INITIAL_TOKEN:
	  printf("yylex returned NAME_INITIAL_TOKEN token (%s)\n", yytext);
          break;
	case ROMANTOKEN:
	  printf("yylex returned ROMANTOKEN token (%s)\n", yytext);
          break;
	case SRTOKEN:
	  printf("yylex returned SRTOKEN token (Sr.)\n");
          break;
	case JRTOKEN:
	  printf("yylex returned JRTOKEN token (Jr.)\n");
          break;
	case EOLTOKEN:
	  printf("yylex returned EOLTOKEN token (%d)\n", EOLTOKEN);
          break;
	case INTTOKEN:
	  printf("yylex returned INTTOKEN token (%d)\n", atoi(yytext));
          break;
	case COMMATOKEN:
	  printf("yylex returned COMMATOKEN token (%d)\n", COMMATOKEN);
          break;
	case DASHTOKEN:
	  printf("yylex returned DASHTOKEN token (%d)\n", DASHTOKEN);
          break;
	case HASHTOKEN:
	  printf("yylex returned HASHTOKEN token (%d)\n", HASHTOKEN);
          break;
	default:
	  exit = true;
	  break;
      }
    }
  }
  else if(strstr(programName,"parser") != NULL) {
    printf("\nOperating in parse mode\n\n");

    switch (yyparse())
    {
    case 0:
      printf("\nParse Successful!\n");
      return 0;
      break;
    case 1:
      printf("\nParse Failed!\n");
      return 1;
      break;
    case 2:
      printf("\nOut of Memory\n");
      return 2;
      break;
    default:	
      printf("\nUnknown result from yyparse()\n");
      return 3;	
      break;
    }
  }
  else {
    printf("\nOperating default mode\n\n");
  }

  return 0;
}
