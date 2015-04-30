/* Daniel Eisterhold
 * dte130030
 * CS 3376.502
 */

%option noinput
%option nounput
%option noyywrap

%{
  #include <stdlib.h>
  #include "parse.h"
%}

%%

([IVXLCDM]+)			{ yylval.roman = strdup(yytext); return ROMANTOKEN; /*Check for Roman Numeral First or it will match a name token*/} 
([0-9]+)                        { yylval.value = atoi(yytext); return INTTOKEN; }
([a-zA-Z]\.?)                   { yylval.nameInitial = strdup(yytext); return NAME_INITIAL_TOKEN; }
([a-zA-Z]{2,})			{ yylval.name = strdup(yytext); return NAMETOKEN; }
([a-zA-Z0-9]+)			{ yylval.identifier = strdup(yytext); return IDENTIFIERTOKEN; }
(Sr.)				{ return SRTOKEN; }
(Jr.)				{ return JRTOKEN; }
([\n])				{ return EOLTOKEN; }
[,]				{ return COMMATOKEN; }
[-]				{ return DASHTOKEN; }
[#]				{ return HASHTOKEN; }
[ \t\r]+			{ /* Do nothing for whitespace */ }

%%

/*
	Program is in "main.c"
*/
