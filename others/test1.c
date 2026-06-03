#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int tmp;
	int x, y;
	int cap;
	int size;
	char *elmts;
} chank;

typedef struct{
	char *name;
	int stor;
} elmnt;

void creat_chank(chank *cnk, int x, int y){
	cnk->cap = 2;
	cnk->size = 0;
	cnk->elmts = malloc(sizeof(elmnt)*cnk->cap);
	cnk->x = x;
	cnk->y = y;
	cnk->tmp = 0;
}

void add_element_2_chank(char *name, chank *cnk){
	int i = 0;
	int exist = 0;
	for(; i < cnk->size; i++){
		if(strcmp(cnk->elmts[i].name, name)){
			exist = 1;
			break;
		}
	}

	if(cnk->size >= cnk->cap){
		cnk->cap *= 2;
		cnk->elmts = realloc(cnk->elmts, sizeof(char));
	}

	if(exist){
		cnk->elmts[i].stor++;
	} else {
		cnk->elmts[cnk->size].name = malloc(sizeof(name));
		strcpy(cnk->elmts[cnk->size].name, name);
		cnk->elmts[snk->size].stor = 1;
		cnk->size++;
	}
}

void remove_element_4m_chank(char *name, chank *cnk){
	for(int i = 0; i < cnk->size; i++){
		if(strcmp(cnk->elmts[i].name, name)){
			cnk->elmts[i].stor--;
		}
	}
}

void free_chank(chank *cnk){
	for(int i = 0; i < cnk->size; i++){
		free(cnk->elmts[i].name);
	}
	free(cnk);
}
