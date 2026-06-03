#include <stdio.h>

int main(){
	for(int i = 0; i < 200; ++i){
		printf("%d : %c",i, i);
		//putchar(i);
		putchar('\n');
	}
}
