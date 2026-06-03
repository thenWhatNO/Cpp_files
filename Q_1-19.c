#include <stdio.h>

#define MAX 1000

void revers_line(char line[], char reversed[]);
void get_line(char line[]);

int main(){
	char line[MAX];
	char reves[MAX];
	int len = 0;

	for(int i = 0; i < MAX; ++i){
		line[i] = reves[i] = 0;
	}

	get_line(line);
	revers_line(line, reves);
	printf("\nreversed line : %s\n", reves);
}

void get_line(char line[]){
	int i, c;
	for(i=0; (c = getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
}

void revers_line(char line[], char revered[]){
	int i;
	int j = 0;
	for(i = MAX; i >= 0; --i){
		if((revered[j] = line[i]) != 0){
			++j;
		}
	}
}
