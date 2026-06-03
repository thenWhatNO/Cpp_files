#ifndef PROCES_H
#define PROCES_H

#define REG_START 10
#define REG_END 350
#define DATA_START 360
#define DATA_END 700
#define LINK_START 710
#define LINK_END 1020

#define PROC_STORE_LEN 1024

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int storeg[PROC_STORE_LEN];
	int regs_ptr;
	int data_ptr;
	int link_ptr;
} proces_t;

int clear_reg(proces_t *pc, int ptr, int type);
int init_proc(proces_t *pc);
int loud_from(memory_t *from, int Fptr, proces_t *to, int Tptr, int sector);
int save_to(proces_t *from, int link, memory_t *to, int Tptr, int sector);
int save_links(proces_t *pc, int link, int size);
int delet_link(proces_t *pc, int link);

int open_file(proces_t *pc, int link, memory_t *mem);

#endif
