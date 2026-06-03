#include <stdio.h>

#define MAXLINE 1000

void getlines(char line[], int lim);

int main(){
	
	int len;
	int max;
	char line[MAXLINE];
	char longs[MAXLINE];

	getlines(line, MAXLINE);

	printf("%s", line);

}

void getlines(char line[], int lim){
	int c, i;
	while((c = getchar()) != EOF && c != '\n'){
		line[i] = c;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
}
