#include <stdio.h>

#define MAX 1000


void clear_buffer(char line[]);
int extracet_line(char line[], char code[], int index);
int check_buffer_for_non_quots(char buffer[]);
void clear_buffer(char line[]);

char test_code[MAX] = "if(1==1){return 1;}\n";

int main(){
	extern char test_code[MAX];
	char line[MAX];
	int reder_index = 0;

	int state;

	//while(reder_index < MAX && state != 1){
		extracet_line(line, test_code, reder_index);
		printf("extracted line ; %s", line);
		state = check_buffer_for_non_quots(line);


		clear_buffer(line);
	//}
	printf("the progrom return : %d\n", state);
}


int extracet_line(char line[], char code[], int index){
	int i = 0;
	int c;
	while((c = line[i] = code[index]) != '\n' && c != 0){
		++i;
		++index;
	}
	return index;
}

// this function check situation like if(){} for(){} while(){}  function(){}
// and return 1 if the { dident come after ) = mean there sould be quots
// 0 if the { come after ) =  mean evreting is fine.
int check_buffer_for_non_quots(char buffer[]){
	int i, c;
	i = 0;

	char in_chake = 0;

	while((c = buffer[i]) != '\n' && c != 0){
		if(c == '#' || i == 0){return 0;}
		if(c == ')' && in_chake == 0){in_chake = 1;}
		if(c == '{' && in_chake == 1){in_chake = 0;}
	}
	return in_chake;
}

void clear_buffer(char line[]){
	for(int i = 0; i < MAX; ++i){
		line[i] = 0;
	}
}

int check_brekets(){
	return 1;
}
