#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>
#include <string.h>

typedef struct {
	char *name;
	int age;
	char *file;
} User;

typedef struct {
	User *data;
	int size;
	int cap;
} Database;

typedef struct {
	char *post;
	char *time;
	char *usr_name;
} Post;

typedef struct {
	Post *posts;
	int size;
	int cap;
} Post_data;

User *curent_usr = NULL;

void creat_Post_base(Post_data *pd){
	pd->size = 0;
	pd->cap = 2;
	pd->posts = malloc(sizeof(Post)*pd->cap);
}

void add_post(char *post, char *name, char *time, Post_data *pd){
	if (pd->size >= pd->cap){
		pd->cap *= 2;
		pd->posts = realloc(pd->posts, sizeof(Post)*pd->cap);
	}

	Post *pst = &pd->posts[pd->size];
	pst->post = malloc(strlen(post)+1);
	pst->usr_name = malloc(strlen(name)+1);

	strcpy(pst->post, post);
	strcpy(pst->usr_name, name);

	pst->time = malloc(strlen(time)+1);
	strcpy(pst->time, time);

	++pd->size;
	free(pst);
}

void creat_Dbase(Database *db){
	db->size = 0;
	db->cap = 2;
	db->data = malloc(sizeof(User)*db->cap);
}

User *find_user(char *name, Database *db){
	for(int i = 0; i < db->size; i++){
		if(strcmp(db->data[i].name, name) == 0){
			return &db->data[i];
		}
	}
	perror("cant find user!\n");
	return NULL;
}

void creat_user_profile(char *name ,Database *db){

	User *usr = find_user(name, db);

	FILE *fptr = fopen(usr->file, "w");

	time_t cur_time;
	char *time_s;

	cur_time = time(NULL);
	if(cur_time == (time_t)(-1)){
		perror("faild the get time\n");
		return;
	}
	time_s = ctime(&cur_time);
	fprintf(fptr ,"the user %s, have been created at : %s", usr->name, time_s);

	fclose(fptr);
}

void add_user(char *name, int age, Database *db){

	if(db->size >= db->cap){
		db->cap *= 2;
		db->data = realloc(db->data, sizeof(User)*db->cap);
	}

	User *usr = &db->data[db->size];

	usr->name = malloc(strlen(name)+1);
	strcpy(usr->name, name);
	usr->age = age;
	usr->file = malloc(strlen(name)+1);
	char file_n[100];
	strcpy(file_n, name);
	strcat(file_n, "_profile.txt");
	strcpy(usr->file, file_n);

	db->size++;
}

void remov_user(char *name, Database *db){
	int idx, del;
	del = 0;

	for(int i = 0; i < db->size; i++){
		if((strcmp(db->data[i].name, name)) == 0){
			printf("delet %s\n\n", db->data[i].name);
			free(db->data[i].name);
			idx = i;
			del = 1;
		}
	}

	if(del){
		for(int i = idx; i < db->size-1; i++){
			db->data[i] = db->data[i+1];
		}
		db->size--;
	} else {printf("%s not found\n\n", name);}
}

void show_user(Database *db){
	for(int i = 0; i < db->size; i++){
		printf("%s %d\n",db->data[i].name, db->data[i].age);
	}
}

void show_all_post(Post_data *pd){
	for(int i = 0; i < pd->size; i++){
		printf("%s [%s]: %s\n", pd->posts[i].usr_name, pd->posts[i].time, pd->posts[i].post);
	}
}

void free_Dbase(Database *db){
	for(int i = 0; i < db->size; i++){
		free(db->data[i].name);
	}
	free(db->data);
	printf("data base was freed\n");
}

void free_Pdata(Post_data *pd){
	for(int i = 0; i < pd->size; i++){
		free(pd->posts[i].post);
		free(pd->posts[i].time);
		free(pd->posts[i].usr_name);
	}
	free(pd->posts);
	printf("post data was freed\n");
}

void save2F(Database *db, char *file){
	FILE *fptr = fopen(file, "w");

	for(int i = 0; i < db->size; i++){
		fprintf(fptr, "%s %d\n", db->data[i].name, db->data[i].age);
	}

	fclose(fptr);
}

void save_post2F(char *file, Post_data *pd){
	FILE *fptr = fopen(file, "w");

	for(int i = 0; i < pd->size; i++){
		fprintf(fptr, "%s %s %s\n",pd->posts[i].usr_name, pd->posts[i].time, pd->posts[i].post);
	}
}

void loud4F(Database *db, char *file){
	FILE *fptr = fopen(file, "r");

	int age = 0;
	char name[100];

	while(fscanf(fptr, "%s %d", name, &age) == 2){
		add_user(name, age, db);
	}


	fclose(fptr);
}

void loud_post4F(char *file, Post_data *pd){
	FILE *fptr = fopen(file, "r");

	char name[100];
	char time[100];
	char post[1000];

	while(fscanf(fptr, "%s %s %s",name, time, post) == 3){
		printf("name: %s time: %s post: %s", name,time, post);

		add_post(post, name, time, pd);
	}
}

void enter_add_user_slot(Database *db){
	printf("enter new user name:  ");
	char name[100];
	scanf("%s", name);
	printf("enter you age:   ");
	int age;
	scanf("%d", &age);

	printf("so your name is %s, and your age is %d? [Y/n]\n", name, age);

	int c = getchar();
	switch ((c = getchar())){
		case 'Y':
			add_user(name, age, db);
			creat_user_profile(name ,db);
		break;
		case 'y':
			add_user(name, age, db);
			creat_user_profile(name ,db);
		break;
		case 'N':
			enter_add_user_slot(db);
		break;
		case 'n':
			enter_add_user_slot(db);
		break;
		default:
			//printf("switch worked %d : %c\n", c,c);
	}
}

void enter_login_user_slot(Database *db){
	extern User *curent_usr;

	printf("type th user name to enter profile...  ");
	char name[100];
	scanf("%s", name);

	curent_usr = find_user(name, db);
	printf("you are enter %s profile !...\n", curent_usr->name);
}

void enter_add_post_slot(Post_data *pd){
	extern User *curent_usr;

	printf("write anything to post, then type ctrl+d to post:\n");

	int c = getchar();
	int cap = 10;
	int size = 0;
	char *pst = malloc(10);
	while((c = getchar()) != '\n'){
		if (size >= cap){
			cap*=2;
			pst = realloc(pst, cap);
		}

		if(c == ' '){c = '_';};
		pst[size] = c;

		++size;
	}

	time_t cur_time;
	struct tm *timeinfo;
	char buff[6];

	time(&cur_time);
	timeinfo = localtime(&cur_time);

	strftime(buff, sizeof(buff), "%H:%M", timeinfo);
	printf("%s", buff);
	add_post(pst, curent_usr->name, buff, pd);

}

void edit_user_profile(){
	extern User *curent_usr;
	if(curent_usr == NULL){
		perror("the user not found");
		return;
	}
	FILE *fptr = fopen(curent_usr->file, "a");

	printf("write anything to add to your profile...\n");
	char buff[1000];

	scanf("%s", buff);
	fprintf(fptr, "\n %s", buff);

	printf("edit the profile -> %s", curent_usr->name);
}

void profile_useg_slot(Post_data *pd){
	extern User *curent_usr;

	int c;
	int run = 1;
	int max_loop = 0;
	while(run){
		printf("welcom to the profile : %s\n\n-> press P to post\n-> press E to edit profile\n-> press X to exit the profile\n", curent_usr->name);
		if(max_loop > 100){run = 0;}
		max_loop++;
		c = getchar();
		switch (c){
			case 'p':
				enter_add_post_slot(pd);
			break;
			case 'P':
				enter_add_post_slot(pd);
			break;
			case 'e': edit_user_profile(); break;
			case 'E': edit_user_profile(); break;
			case 'x': run = 0; break;
			case 'X': run = 0; break;
		}
	}
}

void enter_remove_profile_slot(Database *db){
	char name[100];
	printf("write the name of the profile you want to delet...\n");
	scanf("%s", name);

	printf("deleting the user name %s ?\n [Y/n]", name);

	int c;
	if((c = getchar()) == 'y' || c == 'Y'){
		remov_user(name, db);
	} else if (c == 'n' || c == 'N'){
		printf("stoped the delete opiration\n");
		return;
	}
}

int main(){
	extern User *curent_usr;

	Database data;
	creat_Dbase(&data);

	Post_data post_d;
	creat_Post_base(&post_d);

	loud4F(&data, "saved_data.txt");
	loud_post4F("saved_posts.txt", &post_d);

	int run = 1;
	int c;
	int max_loop = 0;
	while(run){
		if(max_loop > 100){run = 0;}
		max_loop++;

		c = getchar();

		if(curent_usr != NULL){
			profile_useg_slot(&post_d);
			curent_usr = NULL;
		} else {

			printf("type I - to login with name and password\ntype A - to add new user\ntype D - to delet user\ntype P - to view all the posts\n\ntype X - to exit the program\n");
			switch (c){
				case 'A':
					enter_add_user_slot(&data);
				break;
				case 'a':
					enter_add_user_slot(&data);
				break;
				case 'I':
					enter_login_user_slot(&data);
				break;
				case 'i':
					enter_login_user_slot(&data);
				break;
				case 'D':
					enter_remove_profile_slot(&data);
				break;
				case 'd':
					enter_remove_profile_slot(&data);
				break;
				case 'p':
					show_all_post(&post_d);
				break;
				case 'P':
					show_all_post(&post_d);
				break;
				case 'x': run = 0; break;
				case 'X': run = 0; break;
			}
		}
	}


	//show_user(&data);

	save_post2F("saved_posts.txt", &post_d);
	save2F(&data, "saves_data.txt");
	free_Dbase(&data);
	free_Pdata(&post_d);}
