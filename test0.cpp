#include <iostream>

using namespace std;


char** Set_buffer(int x_, int y_, int** snake);
void render(int x_, int y_, char** C_name);
int** set_Snake();

int main(){
	int** snakey = set_Snake();
	char** buffer = Set_buffer(100, 30, snakey);
	render(100, 30, buffer);
	return 0;
}

int** set_Snake(){
	int** snake_body = new int*[300];
	for(int a = 0; a < 300; ++a){
		snake_body[a] = new int[300];
	}
	
	int c = 3;
	for(int i = 0; i < 3; ++i){
		snake_body[0][i] = c;
		--c;		
	}
	return snake_body;
}

char** Set_buffer(int x_, int y_, int** snake){
	char** C_name = new char*[y_];
	for(int i = 0; i < y_; ++i){
		C_name[i] = new char[x_];
	}

	for(int l = 0; l < y_; ++l){
		for (int r = 0; r < x_; ++r){
			C_name[l][r] = '#';
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

