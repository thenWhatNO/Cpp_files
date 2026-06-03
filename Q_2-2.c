#include <stdio.h>

int main(){

	enum chars {LIM = 100};
	int c;
	for(int i = 0; i < LIM; ++i){
		if((c = getchar()) != '\n'){
			if(c != EOF){
				printf("did stuff");
			}
		}
	}
}
