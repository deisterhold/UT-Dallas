/*
*Daniel Eisterhold
*dte130030@utdalals.edu
*CS 3376.502
*/
%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
%}

/*
 * Our tokens are defined here.  They are automatically defined
 * in y.tab.h so we can include that file for the Flex Scanner.
 */

%token	NAMETOKEN
%token  IDENTIFIERTOKEN
%token  NAME_INITIAL_TOKEN
%token  ROMANTOKEN
%token  SRTOKEN
%token  JRTOKEN
%token  EOLTOKEN
%token  INTTOKEN
%token  COMMATOKEN
%token  DASHTOKEN
%token  HASHTOKEN

/*
 * The union is used for setting values in Flex with the yylval
 * variable.  This is how Flex communicates with Bison.
 */					     

%union
{
    int value;
    char *name;
    char *identifier;
    char *nameInitial;
    char *roman;
}

/*			
 * The values in the angle brackets below are the types
 * declared in the union above.  For each COMPLEX TOKEN
 * we need to tell the system where to get its value.
 *			
 * In this case, NAMETOKEN, IDENTIFIERTOKEN, NAME_INITIAL_TOKEN, ROMANTOKEN and INTTOKEN are complex.
 * They values are set in the Flex code and read/used in
 * this file. 						
 */				 			

%type	<value>	INTTOKEN
%type	<name>   NAMETOKEN
%type   <identifier>   IDENTIFIERTOKEN
%type   <nameInitial>   NAME_INITIAL_TOKEN
%type   <roman>   ROMANTOKEN

%start postal_addresses    /* Uses first pattern if not specified */ 

%%

/*
 * Careful here... the very last entry in the source file should not
 * have a double newline.  An extra blank line indicates that another
 * address is starting.
 */

postal_addresses: address_block EOLTOKEN postal_addresses
	| address_block
	;

address_block: name_part street_address location_part
	;

name_part: personal_part last_name suffix_part EOLTOKEN
	| personal_part last_name EOLTOKEN
	| error EOLTOKEN { fprintf(stdout,"Bad name-part... skipping to newline\n"); }

personal_part: NAMETOKEN { fprintf(stderr,"<FirstName>%s<FirstName>\n",$1); }
	| NAME_INITIAL_TOKEN { fprintf(stderr,"<FirstName>%s</FirstName>\n",$1); }
	;

last_name: NAMETOKEN { fprintf(stderr,"<LastName>%s</LastName>\n",$1); }
	;

suffix_part: SRTOKEN { fprintf(stderr,"<Suffix>Sr.</Suffix>\n"); }
	| JRTOKEN { fprintf(stderr,"<Suffix>Jr.</Suffix>\n"); }
	| ROMANTOKEN { fprintf(stderr,"<Suffix>%s</Suffix>\n",$1); }
	;

street_address: street_number street_name INTTOKEN EOLTOKEN { fprintf(stderr,"<AptNum>%d</AptNum>\n",$3); }
| street_number street_name HASHTOKEN INTTOKEN EOLTOKEN { fprintf(stderr,"<AptNum>%d</AptNum>\n",$4); }
| street_number street_name EOLTOKEN
| error EOLTOKEN { fprintf(stdout,"Bad address_line... skipping to newline\n"); }
;

street_number: INTTOKEN { fprintf(stderr, "<HouseNumber>%d</HouseNumber>\n", $1); }
	| IDENTIFIERTOKEN { fprintf(stderr, "<HouseNumber>%s</HouseNumber>\n", $1); }
	;

street_name: NAMETOKEN { fprintf(stderr, "<StreetName>%s</StreetName>\n", $1); }
	;

location_part: town_name COMMATOKEN state_code zip_code EOLTOKEN
	| error EOLTOKEN { fprintf(stdout,"Bad location_line... skipping to newline\n"); }
	;

town_name: NAMETOKEN { fprintf(stderr,"<City>%s</City>\n",$1); }
	;

state_code: NAMETOKEN { fprintf(stderr,"<State>%s</State>\n",$1); }
	;

zip_code: INTTOKEN DASHTOKEN INTTOKEN { fprintf(stderr,"<Zip5>%d</Zip5>\n<Zip4>%d</Zip4>\n\n",$1, $3); }
	| INTTOKEN { fprintf(stderr,"<Zip5>%d</Zip5>\n\n",$1); }
	;

%%

void yyerror(char *s)
{
/*
 *   fprintf(stdout, "Error: %s\n", s);
 */
}
