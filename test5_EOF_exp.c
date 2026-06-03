#include <stdio.h>
#include <string.h>

int main(){
	int c = getchar();
	printf("%d \n", (c != EOF));

	if(c == EOF){
		printf("%d \n", c);
	}
}
