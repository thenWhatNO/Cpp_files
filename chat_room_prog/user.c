#include <stdio.h>
#include <stdlib.h>
#include <strlib.h>
#include "user.h"

void say_hello(){
	printf("hello world!");
}

clinet_meneger *get_CM(){
	clinet_meneger *cm;
	cm->cap = 2;
	cm->size = 0;
	cm->data = malloc(sizeof(clinet)*cm->cap);
	return cm;

}

void free_mc(clinet_meneger *cm){
	for(int i = 0; i < cm->size; i++){
		free(cm->data[i].link);
		free(cm->data[i].port);
		cm->data[i].link = NULL;
		cm->data[i].port = NULL;
	}
	free(cm);
	cm = NULL;
}

void add_clinet(char *link, char *port, clinet_meneger *cm){
	if(cm->size >= cm->cap){
		cap *= 2;
		cm->data = realloc(cm->data, sizeof(clinet)*cm->cap);
	}

	cm->data[cm->size].link = malloc(sizeof(link)+1);
	cm->data[cm->size].port = malloc(sizeof(port)+1);

	strcpy(cm->data[cm->size].link, link);
	strcpy(cm->data[cm->size].port, port);

	cm->size++;

}

void remov_clinet(char *link, clinet_meneger *cm){
	int rmv = 0;
	for(int i = 0; i < cm->size, i++){
		if(strcmp(cm->data[i].link, link) == 0){
			free(cm->data[i].link);
			free(cm->data[i].port);
			cm->data[i].link = NULL;
			cm->data[i].port = NULL;
			rmv = 1;
		}
		if(rmv){
			cm->data[i] = cm->data[i+1];
		}
	}
}
