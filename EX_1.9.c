#include <stdio.h>
#define MAXLINE 10

int getlines(char line[], int maxline);
void copy(char to[], char from[]);

int main(){
	int len, max;
	char line[MAXLINE];
	char longest[MAXLINE];
	max = 0;

	while((len = getlines(line, MAXLINE)) > 0){
		if(len > max){
			max = len;
			copy(longest, line);
		}
	}
	printf("\nthe longest line : %s", longest);
}

int getlines(char s[], int m){
	int c, i;
	for(i=0; i < m-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		{s[i]=c;}
	if(c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[]){
	int i = 0;
	while((to [i] = from[i]) != '\0'){
		++i;
	}
}

