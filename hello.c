#include <stdio.h>
#include <stdbool.h>

bool check_sting(char str1[10], char str2[10]);

int main(){
	char input[10];
	char rel_pass[10] =  "lamana";
	
	printf("enter ur pass \n");

	scanf("%s", input);
	
	int atempt = 5;
	while(atempt > 0){
		if (check_sting(input, rel_pass)){
			printf("yay you enterd\n");
			return 1;
		}
		else{
			atempt--;
			printf("no the right one, try again : \n");
			scanf("%s", input);
		}
	}
	
	printf("u ran out of atempts >:(");

	return 1;
}

bool check_sting(char str1[10], char str2[10]){
	for (int i = 0; i < 10; i++){
		if(str1[i] != str2[i]){
			return false;
		}
	}
	return true;
}
