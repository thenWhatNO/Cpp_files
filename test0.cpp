#include <iostream>

using namespace std;


char Set_buffer(int x_, int y_);
void render(int x_, int y_);
int set_Snake();

int main(){
	int snakey[300][300] = set_snake();
	char buffer = Set_buffer(100, 30, snakey);
	render(100, 30, buffer);
	return 0;
}

int set_Snake(){
	int snake_body[300][300];
	
	int c = 3;
	for(int i = 0; i < 3; ++i){
		snake_body[0][i] = c;
		--c;		
	}
	return snake_body;
}

char Set_buffer(int x_, int y_, int snake[300][300]){
	char C_name[y_][x_];

	for(int l = 0; l < y_; ++l){
		for (int r = 0; r < x_; ++r){
			C_name[l][r] = '#';
		}
	}
	return C_name;
}

void render(int x_, int y_, char C_name[100][30]){
	for (int row = 0; row < y_; ++row){
		for(int col = 0; col < x_; ++col){
			cout << C_name[row][col];
		}	
		cout << '\n';
	}	
}

