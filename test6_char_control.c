#include <stdio.h>

int main(){
	int c, ln = 0;
	while((c = getchar()) != EOF){
		if(c == '\n' || c == '\t' || c == ' '){
			++ln;
		}

		//printf("%d\n", c);
		switch (c){
			case '\n':
				putchar(92);
				putchar('n');
			break;
			case '\t':
				putchar(92);
				putchar('t');
			break;
			default:
			putchar(c);
		}
	}
	printf("%d\n", ln);
}
