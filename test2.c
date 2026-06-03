
#include <stdio.h>

int main(){
	int c, countN, wordN;
	int langh[15] = {0};

	countN = wordN = 0;

	while((c = getchar()) != EOF){

		++countN;
		if(c == ' ' || c == '\n' || c == '\t'){
			langh[wordN] = countN;
			countN = 0;
			++wordN;
		}
	}

	for(int i = 0; i < wordN; ++i){
		printf("word : ");
		for (int ii = 0; ii < langh[i]; ++ii){
			putchar('#');	
		}
		putchar('\n');
	}
}
