/*
* Name: ifxr
* Date: 17 May 2023
*/
#include "getword.h"

/*
* Main function serves to test whether "getword" is returning the correct values.
* Ex: s = "Null&void" c = 4, 1, 4
* Ex: s = "Null/&void" c = 9
*/
int main(){
	int c;
	char s[STORAGE];
	
	for(;;){
		(void) printf("n=%d, s=[%s]\n", c = getword(s), s);
		if (c == -1) break;
	}
}
