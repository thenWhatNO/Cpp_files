#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sstream>

using namespace std;

char** Set_buffer(int x_, int y_, string* snake);
void render(int x_, int y_, char** C_name);
string* set_Snake();
void updata_snake(string* snake, char last_move);
char get_c();

int main(){
	string* snakey = set_Snake();
	char** buffer = Set_buffer(100, 30, snakey);
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

	return snake_body;
}

string* updata_snake(string* snake, char last_move){

	tringstream ss(snake[snake_point]);
	int S_x, S_y;
	char comma;
	ss >> S_y >> comma >> S_x;

	switch(last_move){
		case 'w':
			--S_y;
			break;
		case 'd':
			++S_x;
			break;
		case 's':
			++S_y;
			break;
		case 'a':
			--S_x;
			break;
	}	
	

}

char** Set_buffer(int x_, int y_, string* snake){
	char** C_name = new char*[y_];
	for(int i = 0; i < y_; ++i){
		C_name[i] = new char[x_];
	}

	int snake_point = 0;
	for(int l = 0; l < y_; ++l){
		for (int r = 0; r < x_; ++r){
			stringstream ss(snake[snake_point]);
			int S_x, S_y;
			char comma;
			ss >> S_y >> comma >> S_x;
			if(S_y == l && S_x == r){
				cout << snake[snake_point] << endl;
				C_name[l][r] = 's';
				++snake_point;
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

