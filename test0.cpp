#include <iostream>

using namespace std;

void func();

int main(){
	std::cout  << "hello world" << std::endl;
	return 0;
}

void func(){
	int i;
	for(int a = 0; a < 10; a++){
		cout << a << endl;	
	}
}
