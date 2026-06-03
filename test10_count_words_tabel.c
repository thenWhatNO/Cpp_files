#include <stdio.h>

#define OUT 0
#define IN  1

int main(){
	int c, ward, chars, index, sub_ind, state;
	int words[10][10];
	int word_num[10];
	state = OUT;
	ward = chars = index = sub_ind = 0;
	for(int i = 0; i < 10; ++i){
		word_num[i] = 0;
		for(int j = 0; j < 10; ++j){
			words[i][j] = 0;
		}
	}

	while((c = getchar()) != EOF){
		if(c == '\n' || c == '\t' || c == ' ' && state == IN){
			state = OUT;
			++index;
			sub_ind = 0; 
		}
		if(c != '\n' && c != '\t' && c != ' '){
			state = IN;
			++word_num[index];
			words[index][sub_ind] = c;
			++sub_ind;
		}
	}
	putchar('\n');
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			putchar(words[i][j]);
		}
		putchar('\t');
	}
	putchar('\n');
	for(int i = 0; i < 10; ++i){
		printf("%d\t", word_num[i]);
	}
}
