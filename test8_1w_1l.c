#include <stdio.h>

#define IN  1
#define OUT 0

int main(){
	int c, state;
	c = 0;

	while((c = getchar()) != EOF){
		if(c == '\n' || c == '\t' || c == ' '){putchar('\n');}
		else {putchar(c);}
	}
}
