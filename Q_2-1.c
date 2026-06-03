#include <stdio.h>
#include <limits.h>

int main(){
	printf("%d\n", INT_MAX);
	printf("%d\n", UINT_MAX);

	int max_int;
	int min_int;
	short int sor_max;
	short int sor_min;
	max_int = min_int = sor_max = sor_min = 0 ;
	for(int i = 0; 1==1;++i){
		printf("\033[2J");
		printf("\033[H");
		++max_int;
		++sor_max;
		--min_int;
		--sor_min;
		printf("%d\n%d\n%d\n%d", max_int, min_int, sor_max, sor_min);
	}

}
