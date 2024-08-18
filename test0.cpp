#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sstream>
#include <string>

using namespace std;

char** Set_buffer(int x_, int y_, string* snake);
void render(int x_, int y_, char** C_name);
string* set_Snake();
string* updata_snake(string* snake, char last_move, int snakee_langh);
char get_c();
bool snake_in(int Y, int X, int langh);

int main(){
	string* snakey = set_Snake();
	char** buffer = Set_buffer(100, 30, snakey);
	render(100, 30, buffer);
	updata_snake(snakey, 'd', 1);
	render(100, 30, buffer);	
	
	//delete datas

	for(int a = 0; a < 30; ++a){
		delete[] buffer;
	}
	delete[] buffer;

	delete[] snakey;

	return 0;
}

char get_c(){
	struct termios oldt, newt;
	char ch;

	if(tcgetattr(STDIN_FILENO, &oldt) != 0){
		perror("tcgtattr");
		return -1;
	}

	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);

	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0){
		perror("tcsetattr");
		return -1;
	}

	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0){
		perror("tcsetattr");
		return -1;
	}

	return ch;
}

string* set_Snake(){
	string* snake_body = new string[300];

	for (int i = 0; i < 300; ++i){
		snake_body[i] = "";
	}

	snake_body[0] = "0, 3";
	snake_body[1] = "0, 2";

	return snake_body;
}

string* updata_snake(string* snake, char last_move, int snakee_langh){

	int snake_point = 0;
	int prev_stap[2] = {0};
	int new_step[2] = {0};
	for (int i = 0; i < snakee_langh; ++i){
		stringstream ss(snake[i]);
		int S_x, S_y;
		char comma;
		ss >> S_y >> comma >> S_x;
		prev_stap[0] = S_y; prev_stap[1] = S_x;

		cout << prev_stap[0] << prev_stap[1] << endl;

		if (snake_point == 0){
			switch(last_move){
				case 'w':
					new_step[1] = S_x;
					new_step[0] = --S_y;
					break;
				case 'd':
					new_step[0] = S_y;
					new_step[1] = ++S_x;
					break;
				case 's':
					new_step[1] = S_x;
					new_step[0] = ++S_y;
					break;
				case 'a':
					new_step[0] = S_y;
					new_step[1] = --S_x;
					break;
			}
			cout << new_step[0] << new_step[1] << endl;
		}
		else{

		}
		snake[i] = to_string(new_step[0]) + ", " + to_string(new_step[1]);
		new_step[0] = prev_stap[0]; new_step[1] = prev_stap[1];
	}
	
	return snake;
}

bool snake_in(int Y, int X, int langh, string* snake){
	for(int i = 0; i < langh; ++i){
		stringstream ss(snake[i]);
		int S_x, S_y;
		char comma;
		ss >> S_y >> comma >> S_x;

		if (Y == S_y && X == S_x){
			return true;
		}
	}
	return false;
}

char** Set_buffer(int x_, int y_, string* snake){
	char** C_name = new char*[y_];
	for(int i = 0; i < y_; ++i){
		C_name[i] = new char[x_];
	}

	for(int l = 0; l < y_; ++l){
		for (int r = 0; r < x_; ++r){
			if(snake_in(l, r, 2, snake)){
				C_name[l][r] = 's';
			}
			else {
				C_name[l][r] = '#';
			}
		}
	}
	return C_name;
}

void render(int x_, int y_, char** C_name){
	for (int row = 0; row < y_; ++row){
		for(int col = 1; col < x_; ++col){
			cout << C_name[row][col];
		}	
		cout << '\n';
	}	
}

