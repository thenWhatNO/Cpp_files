#ifndef MEMORY_H
#define MEMORY_H

typedef struct {
	int data[2048];
	int ptr;
} memory_t;

int init_memory(memory_t *mem);

#endif
