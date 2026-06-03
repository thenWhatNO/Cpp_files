#include <stdio.h>

#define MAX 10

void copy(char from[], char to[]);
int getline_len(char line[]);

int main(){

	int len, max;
	char cor_line[MAX];
	char longest_line[MAX];
	len = max = 0;
	while(len = getline_len(cor_line)){
		if(len > max){
			max = len;
			copy(cor_line, longest_line);
		}
	}
	printf("\nthe longest line : %swithe lengh of : %d\n", longest_line, max);
}

int getline_len(char line[]){
	int c, i, index;
	for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i){
		if(i < MAX-1){
			index = i;
			line[index] = c;
			}
	}
	if(c == '\n'){
		line[index] = c;
		++index;
	}
	line[index] == '\0';
	return i;
}

void copy(char from[], char to[]){
	int i = 0;
	while((to[i] = from[i]) != '\0'){++i;}
}
