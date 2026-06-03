#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define WOL_RAN 100

void render_map();
int user_input();
void game_loop();
void rearange_snake();
void update_map();
int check_snake_present(int x, int y, int snake[]);

int main(){
	printf("hello wolrd!");

	while(1==1){
	
	}
}

void render_map(){
	extern int map[][WOL_RAN];
	printf("\033[2J");
	printf("\033[H");
	for(int x = 0; x < WOL_RAN; ++x){
		for(int y = 0; y < WOL_RAN; ++y){
			if(map[x][y] == 0){
				putchar(' ');
			}else{
				putchar('#');
			}
		}
		putchar('\n');
	}
}

void rearange_snake(int snake[]){
	int c = user_input();
	int off_set[2] = {0,0};
	switch (c){
		case 'w':
			++off_set[0];
		break;
		case 'a':
			--off_set[1];
		break;
		case 'd':
			++off_set[1];
		break;
		case 's':
			--off_set[0];
		break;
	}
	for(int i = 0; i < 2; ++i){
		snake[i] += off_set[i];
	}
}

int check_snake_present(int x, int y, int snake[]){
	if(snake[0] == x && snake[1] == y){return 1;}
	return 0;
}

void update_map(int map[][WOL_RAN], int snake[]){
	for(int i = 0; i < WOL_RAN ; ++i){
		for(int j = 0; j < WOL_RAN; ++i){
			if(check_snake_present(i,j, snake)){
				map[i][j] = 1;
			}
		}
	}
}

int user_input(){
	int c;
	c = getchar();
	return c;
}
