#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#define WOLD 60
#define SNAK 60

void creat_new_frute();

int map[WOLD/2][WOLD];
int snake[SNAK][2];
int snake_len = 1;
int user_input;
int frute [2];
int running = 1;
int milsec = 300000;


struct termios original, raw;

void render_map(){
	extern int map[][WOLD];

	for(int x = 0; x < WOLD/2; ++x){
		for(int y = 0; y < WOLD; ++y){
			//printf("%d", map[x][y]);
			if(map[x][y] == 0){printf(" ");}
			if(map[x][y] == 1){printf("@");}
			if(map[x][y] == 2){printf("#");}
			if(map[x][y] == 3){printf("X");}
		}
		printf("\n");
	}
}

void assain(int *to, int *from, int index){
	for(int i = 0; i < index; ++i){
		to[i] = from[i];
	}
}

void odred_s(int step[]){
	extern int snake[][2];

	int new_step[2];
	int old_step[2] = {0};
 
	assain(new_step, snake[0],2);

	snake[0][0] += step[0];
	snake[0][1] += step[1];

	if(snake_len <= 1 || snake[0][0] == new_step[0] && snake[0][1] == new_step[1]){
		return;
	}

	for(int i = 1; i < SNAK; ++i){
		assain(old_step, snake[i], 2);
		assain(snake[i], new_step, 2);
		assain(new_step, old_step, 2);
	}
}


void update(){
	extern int map[][WOLD];
	extern int snake[][2];
	extern int user_input;
	extern int frute[];
	extern int snake_len;
	extern int running;
	extern int milsec;


	int snake_pos[2] = {0,0};

	switch(user_input){
		case 'w':
			--snake_pos[0];
		break;
		case 's':
			++snake_pos[0];
		break;
		case 'a':
			--snake_pos[1];
		break;
		case 'd':
			++snake_pos[1];
		break;
	}

	odred_s(snake_pos);

	for(int x = 0; x < WOLD/2; ++x){
		for(int y = 0; y < WOLD; ++y){
			map[x][y] = 0;
			// see cnake pos
			for(int i = 0; i < snake_len; ++i){
				if(snake[i][0] == x && snake[i][1] == y){
					map[x][y] = 1;
				}
			}

			// world borders
			if(x == 0 || x == (WOLD/2)-1 || y == 0 || y == WOLD-1)
				{map[x][y] = 2;}

			if(frute[0] == x && frute[1] == y){map[x][y] = 3;}

			//
			if(snake[0][0] == frute[0] && snake[0][1] == frute[1]){
				creat_new_frute();
				++snake_len;
				if(milsec > 150000){
					milsec -= 100;
				}
			}
			if(snake[0][0] <= 0 || snake[0][0] >= (WOLD/2)-1 || snake[0][1] <= 0 || snake[0][1] >= WOLD-1){
				user_input = EOF;
				running = 0;
			}

			for(int i = 1; i < snake_len; ++i){
				if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]){
					running = 0;}
			}
		}
	}
}

void creat_new_frute(){
	extern int snake[][2];
	extern int frute[];

	int x = (rand() % (WOLD/2)-2) + 1;
	int y = (rand() % WOLD-2) + 1;

 	for(int i = 0; i < SNAK; ++i){
		if (x == snake[i][0] || x <= 0 || x >= (WOLD/2)-1){
			x = (rand() % (WOLD/2)-1) + 2;}
		if (y == snake[i][1] || x <= 0 || x >= WOLD-1){
			y = (rand() % WOLD-1) + 2;}
	}
	frute[0] = x;
	frute[1] = y;
}

int main(){
	extern int map[][WOLD];
	extern int snake[][2];
	extern int user_input;
	extern int frute[];
	extern int running;
	extern int milsec;
	extern struct termios original, raw;


        tcgetattr(STDIN_FILENO, &original);
        raw = original;

        raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);

	snake[0][0] = WOLD/4;
	snake[0][1] = WOLD/2;

	creat_new_frute();

	for(int x = 0; x < WOLD/2; ++x){
		for(int y = 0; y < WOLD; ++y){
			map[x][y] = 0;
		}
	}

	char lst = 'd';

	while(running){

		fd_set set;
		struct timeval timeout;

		FD_ZERO(&set);
		FD_SET(STDIN_FILENO, &set);

		timeout.tv_sec = 0;
		timeout.tv_usec = milsec;

		int ready = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

		if(ready > 0){
			user_input = getchar();
		} else if (ready == 0){
			user_input = lst;
		} else {
			perror("select");
			break;
		}

		fflush(stdout);

		system("clear");
	printf("%d  %d\n", frute[0], frute[1]);
		update();
		render_map();
		lst = user_input;
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &original);
	printf("the game hase stoped!");
}
