#include <stdio.h>

void render(char *chars, int *numb, int size);

int main(){
	int c, isIn, wordN;
	char chars_in[25] = {' '};

	for(int i = 0; i < 25; ++i){
		chars_in[i] = ' ';
	}

	int num_of_char[25] = {0};

	isIn = wordN = 0;

	while((c = getchar()) != EOF){
		isIn = 0;
		for(int i = 0; i < 25; ++i){
			if(c == chars_in[i] && c != ' '){
				num_of_char[i] += 1;
				isIn = 1;
			}
		}
		if(isIn == 0 && c != ' ' && c != '\n' && c != '\t'){
			chars_in[wordN] = c;
			num_of_char[wordN] += 1;
			++wordN;
		}
	}

	int is_space = 0;

	putchar('\n');
	for(int i = 0; i < 25; ++i){
		if(chars_in[i] == ' '){
			break;
		}
		putchar(chars_in[i]);
		printf(" : ");
		for(int ii = 0; ii < num_of_char[i]; ++ii){
			putchar('#');
		}
		putchar('\n');
	}

	render(chars_in, num_of_char, wordN);
}

void render(char *chars, int *numb, int size){

	for(int i = 6; i > 0; --i){
	
		for(int ii = 0; ii < size; ++ii){
			if(numb[ii] >= i){
				putchar('#');
			}		
			else{
			putchar(' ');
			}
		}
		putchar('\n');
	}
	for(int i = 0; i < 25; ++i){
		putchar(chars[i]);
	}
}














