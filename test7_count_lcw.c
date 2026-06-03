#include <stdio.h>

#define IN  1
#define OUT 0

int main(){
	int c, wn, ln, cn, state;
	wn = ln = cn = 0;
	while((c = getchar()) != EOF){
		if(c == '\t' || c == ' ' && state == IN){
			state = OUT;}
		if(c == '\n' && state == IN){
			++ln;
			state = OUT;}
		if(c != '\n' || c != '\t' || c != ' '){
			if(state == OUT){++wn;}
			cn++;
			state = IN;
		}
	}
	printf("\nwords : %d, lines : %d, chars : %d \n", wn, ln, cn);
}
