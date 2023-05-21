/*
	Name:
	Instructor:
	Course:
	Due Date:
*/

/*
	Project Description - This file 'getword.c' will aid 'main.c' to create a simple lexical analyzer. This analyzer
	will be able to parse a string and return both valid words and meta-characters ('<', '>', '>&', '>>', '>>&', 
	'|' and '&'). This program will also return the proper length for the given string.
*/

#include "getword.h"
//TODO: backslash effect

int getword(char *w){
	int c;				// integer value of the character inserted by user
	w[0] = '\0';			// Will 'empty' the char *w
	int spaceCount = 0;		// Will keep track of the amount of spaces

	while (( c = getchar()) != '\0'){
		char temp = c;					// Makes it easier to convert and append to a string

		// Checks to see whether the 'w' pointer is less than STORAGE - 1 (254)
		if (strlen(w) == STORAGE -1){
			ungetc(c, stdin);
			return (int)strlen(w);
		}

		// Checks to see whether the character is a letter
		if(((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')|| c == '(' || c == ')' || c == '@' || c == '_'|| c == '+') && w[0] != '>')
			strncat(w, &temp, 1);
		// Checks to see that the chracter is a valid number as well as a period or a dash
		else if (((c>= 48 && c<= 57) || (c == '.') || ( c == '-') || (c == '!') || (c == '/') || (c == '"') || (c=='#') || (c==':')) && w[0] != '>')
			strncat(w, &temp, 1);
		else{
			//Handles metacharacters '>>' and >&'
			if(strlen(w) == 0 && c == '>'){
				strncat(w, &temp, 1);
				continue;
			}
			else if(c == '>' && strlen(w) > 0&& w[0] != '>')
				ungetc(c, stdin);
			// when string length > 0,  will reinsert these metacharacters back on stdin
			else if(( c == '&' || c == '|' || c == '<') && strlen(w) > 0)
				ungetc(c, stdin);
			// Handles the '&', '|', and the '<' meta characters
			else if(( c == '&' || c == '|' || c == '<') && strlen(w) == 0)
				strncat(w, &temp, 1);
			// Handles newline characters
			else if(c == '\n' && strlen(w) > 0)
				ungetc(c, stdin);
			// Handles spaces
			else if (c == ' '&& strlen(w) ==0){
				spaceCount++;

				if (spaceCount>=1)
					continue;
			}//Handles EOF and 'end.' termination commands
			else if(c == EOF || (strcmp(w, "end.") == 0))
				return -1;
		
			spaceCount = 0;	
			return (int)strlen(w);
		}
	
	// Terminates the program if user types 'end.'`
	if(strcmp(w, "end.") == 0)
			return -1;

	}
	return 0;
}
