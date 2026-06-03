#include <stdio.h>

int pawer(int n, int m);

int main(){
	int input = pawer(2, 5);
	printf("\n2 pawer 5 is %d \n", input);
}

int pawer(int n, int m){
	int num = 1;
	for(int i = 0; i < m; ++i){
		num = num * n;
	}
	return num;
}
