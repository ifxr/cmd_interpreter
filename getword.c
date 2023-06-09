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
	int spaceCount = 0;		// Will keep track of the amount of spaces
	int backslashCount = 0;		// Will indicate if the program has encountered a backslash. 0: NO, 1: YES
	int bsEffect = 0;		// Will indicate if character preceding backslash will be affected by it
	w[0] = '\0';			// Will 'empty' the char *w

	while (( c = getchar()) != '\0'){
		char temp = c;					// Makes it easier to convert and append to a string

		// Checks to see whether the 'w' pointer is less than STORAGE - 1 (254)
		if (strlen(w) == STORAGE -1){
			ungetc(c, stdin);
			return (int)strlen(w);
		}
		
		// Checks to see whether the character is a letter or a valid symbol when bsEffect is active
		if(((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '(' || c ==  ')'||c == '@' || c == '_' || c == '+')&& w[0] == '>' && bsEffect == 1){	
			strncat(w, &temp, 1);
			continue;
		}// Checks to see whether the character is a valid number or a valid symbol when bsEffect is active 
		else if (((c>= 48 && c<= 57) || (c == '.') || ( c == '-') || (c == '!') || (c == '/') || (c == '"') || (c=='#') || (c==':'))&& w[0] == '>' && bsEffect == 1){
			strncat(w, &temp, 1);
			continue;
		} 
		// Checks to see whether the character is a letter or a valid symbol
		else if(((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')|| c == '(' || c == ')' || c == '@' || c == '_'|| c == '+') && w[0] != '>')
			strncat(w, &temp, 1);
		// Checks to see that the character is a valid number or a valid symbol
		else if (((c>= 48 && c<= 57) || (c == '.') || ( c == '-') || (c == '!') || (c == '/') || (c == '"') || (c=='#') || (c==':')) && w[0] != '>')
			strncat(w, &temp, 1);
		else{
			// Will filter out '\' metacharacter and activate the backslash and bsEffect variables
			if(c == '\\' && backslashCount == 0){
				backslashCount = 1;
				bsEffect = 1;
				continue;
			}

			// if backslash occurs, it will append the folowing character/meta-character
			if(backslashCount == 1){
				if(c==' ' || c=='<' || c=='>' || c=='&' || c=='|' || c=='\\' ){
					strncat(w, &temp, 1);
					backslashCount = 0;
					continue;
				}				
			}

			// Handles metacharacters: '>>' and '>&'
			if(strlen(w) == 1 && w[0] == '>' && c != ' '){
				if (c == '>'){
	           		strncat(w, &temp, 1);
			   		continue;
				}
				else if (c == '&'){
                    strncat(w, &temp, 1);
	                continue;
                }
				else
  		            ungetc(c, stdin);
			 }
			// Handles metacharacter: '>>&'
			else if( strlen(w) == 2 && w[0] == '>' && w[1] == '>' && c != ' ' ){
				if(c == '&'){
					strncat(w, &temp, 1);
					continue;
				}
				else
					ungetc(c, stdin);
			}
			else if(strlen(w) == 0 && c == '>'){
				strncat(w, &temp, 1);
				continue;
			}
			else if(c == '>' && strlen(w) > 0&& w[0] != '>')
				ungetc(c, stdin);	
			// Will put back the last character back on stream
			// Fixes bug where the first letter gets clipped when using metachar: '>>', '>&' and '>>&'
			else if(strlen(w) == 3 && c != ' ')
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
			else if (c == ' ' && strlen(w) ==0){
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
