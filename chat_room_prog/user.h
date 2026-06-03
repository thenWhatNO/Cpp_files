#ifndef USER
#define USER

typedef struct {
	char *link;
	char *port;
} clinet;

typedef struct {
	clinet *data;
	int size;
	int cap;
} clinet_meneger;

clinet_meneger *get_CM();
void free_CM(clinet_meneger *cm);

void say_hello();

void add_clinet(char *link, char *port, clinet_meneger *cm);
void remov_clinet(char *link, clinet_meneger *cm);


#endif

