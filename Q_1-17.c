#include <stdio.h>

#define MAX 1000
#define MAL 10

int save_line(char from[], char to[], int index);
int get_line(char line[]);

int main(){
	int len = 0;
	int index = 0;
	char line[MAX];
	char saved[MAX];

	while((len = get_line(line)) > 0){
		if(len > MAL){
			index = save_line(line, saved, index);
		}
	}

	printf("\nthe line longer then 20 char : \n%s\n\nthe index : %d\n", saved, index);
}

int get_line(char line[]){
	int c, i;
	for(i =0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

int save_line(char from[], char to[], int index){
	int i=0;
	while((to[index] = from[i]) != '\0'){
		++i;
		++index;
	}
	return index;
}
