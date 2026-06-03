#include <stdio.h>

int main(){
	int c, sn, others;
	int dig[10];

	sn = others = 0;

	for(int i = 0; i < 10; ++i){
		dig[i] = 0;
	}

	while((c = getchar()) != EOF){
		if(c >= '0' && c <= '9'){
			++dig[c-'0'];
		}
		if(c == ' ' || c == '\n' || c == '\t'){
			++sn;
		}
		else{
			++others;
		}
	}

	printf("\ndigit : ");
	for(int i = 0; i < 10; ++i){
		printf(" %d", dig[i]);
	}
	printf("\nothers : %d, sn : %d", others, sn);
}

