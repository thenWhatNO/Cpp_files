#include <stdio.h>

typedef struct{
	int pnt;
	int mamary[1000];
	int regs[4];
	int pc;
} vm;

/*
0 = exit the program run, secend value = mamory slot, tordh value = 1 erturn true/ 0 return false
1 = loud from momory to regir
2 = loude from regis to memory
3 = assain register with value
4 = jump to line in program, secend value = line addres, thered valuse = how mach times to jump(good for loops);

5 = add reg to reg;
6 = minus reg to reg;

7 = 	push data from reg to mamory array(stated with adres 100),
	it look for the free slot, and save the dsta there,
	no need to declear addres, its automatecly save for the first mamory slot it find.
	secend value = reg addres, thered value = (1 = push)/(0 = pop from end)
*/

int program[20] = {
	3, 0, 5,
	7, 0, 1,
	4, 1, 3,	//test the new push pop function!
};

int read_file(vm *test, int *prog){

	while(1){
		int pnt = prog[test->pc++];

		if(pnt == 0){
			int mar = prog[test->pc++];
			int ret = prog[test->pc++];
			if(ret){
				return test->mamary[mar];
			} else {return 0;}
		}
		if(pnt == 1){
			int mer = prog[test->pc++];
			int reg = prog[test->pc++];
			test->regs[reg] = test->mamary[mer];
		}
		if(pnt == 2){
			int reg = prog[test->pc++];
			int mer = prog[test->pc++];
			test->mamary[mer] = test->regs[reg];
		}
		if(pnt == 3){
			int reg = prog[test->pc++];
			int val = prog[test->pc++];
			test->regs[reg] = val;
		}
		if(pnt == 4){
			int line = prog[test->pc++];
			int count = test->pc++;
			if(prog[count] > 0){
				prog[count]--;
				test->pc = 3*line;
			}
		}
		if(pnt == 5){
			int reg1 = prog[test->pc++];
			int reg2 = prog[test->pc++];
			test->regs[reg1] += test->regs[reg2];
		}
		if(pnt == 6){
			int reg1 = prog[test->pc++];
			int reg2 = prog[test->pc++];
			test->regs[reg1] -= test->regs[reg2];
		}
		if(pnt == 7){
			int reg = prog[test->pc++];
			int act = prog[test->pc++];
			if(act = 1){
				test->mamary[test->pnt++] = test->regs[reg];
			}
			if(act = 0){
				test->mamary[test->pnt--] = 0;
			}
		}
	}
}

int main(){
	vm test = {0};
	test.pnt = 100;
	extern int program[];

	int get_num = read_file(&test, program);

	for(int i = 100; i < 1000; i++){
		printf("%d ",test.mamary[i]);
	}

	//return get_num;
}
