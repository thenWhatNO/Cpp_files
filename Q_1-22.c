#include <stdio.h>

#define MAX 100


char line[MAX];
int max_line = 10;

int get_line();

int main(){
	extern char line[];
	int len, index;
	index = 0;
	while((len = get_line()) > 0){
		for(int i = 0; i < len+1; ++i){
			putchar(line[i]);
			if(index >= max_line){
				putchar('\n');
				index = 0;
			} else {
				++index;
			}
		}
	}
}

int get_line(){
	extern int max_line;
	extern char line[];
	int c, i;
	i = 0;
	while((c = getchar()) != EOF && c != '\n'){
		line[i] = c;
		++i;
	}
	if(c != '\n'){
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}
