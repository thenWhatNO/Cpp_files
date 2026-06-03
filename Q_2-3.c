#include <stdio.h>

int char2int(char c);

int main(){
	char string[30] = "0123456789abcdefABCDEF";
	for(int i = 0; i < 30; ++i){
		int c = char2int(string[i]);
		printf("%d\n", c);
	}
}

int char2int(char c){
	if(c >= '0' && c <= '9'){
		return c - 48;
	}
	if(c >= 'A' && c <= 'F'){
		return c - 55;
	}
	if(c >= 'a' && c <= 'f'){
		return c - 87;
	}
}
