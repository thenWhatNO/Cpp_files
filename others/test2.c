#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	int cap;
	int size;
	char words;
} hold_inst;

typedef struct {
	char codon[4];
	int num[3];
} codonN;

typedef struct {
	int size;
	int cap;
	codonN *cdns;
} CDN_hashcod;


void creat_hash_cod(CDN_hashcod *hh){
	hh->size = 0;
	hh->cap = 20;
	hh->cdns = malloc(sizeof(codonN) * hh->cap);
}

void add_codon(CDN_hashcod *hh, char *codon){
	if(hh->size >= hh->cap){
		hh->cap *= 2;
		hh->cdns = realloc(hh->cdns, sizeof(codonN)*hh->cap);
	}

	int exist = 0;
	for(int i = 0; i < hh->size-1; i++){
		if(strcmp(codon, hh->cdns[hh->size].codon) == 0){exist = 1;}
	}

	if(exist){
		perror("codon exist");
		return;}

	strcpy(hh->cdns[hh->size].codon, codon);
	hh->cdns[hh->size].num[0] = 0 + rand() % (255 - 0 + 1);
	hh->cdns[hh->size].num[1] = 0 + rand() % (255 - 0 + 1);
	hh->cdns[hh->size].num[2] = 0 + rand() % (255 - 0 + 1);

	hh->size++;
}

int read_file(char *file, char **buff){
	FILE *ptr = fopen(file, "r");

	if(ptr == NULL){
		perror("cant find file\n");
		return -1;}
	fseek(ptr, 0, SEEK_END);
	long full_len = ftell(ptr);
	rewind(ptr);

	*buff = malloc(sizeof(char)*(full_len+1));
	size_t file_len = fread(*buff, 1, full_len, ptr);
	(*buff)[file_len] = '\0';
	fclose(ptr);

	return full_len;
}

void translt_codon_2_acid(char *codon, char *buff, int rgb[]){
	if(strcmp("TTT", codon)==0){strcpy(buff, "phe"); rgb[0]=102;rgb[1]=255;rgb[2]=153; return;}
	if(strcmp("TTC", codon)==0){strcpy(buff, "phe"); rgb[0]=102;rgb[1]=255;rgb[2]=153; return;}
	if(strcmp("TTA", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("TTG", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("CTT", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("CTC", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("CTA", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("CTG", codon)==0){strcpy(buff, "leu"); rgb[1]=100; return;}
	if(strcmp("ATT", codon)==0){strcpy(buff, "ile"); rgb[0]=255;rgb[1]=255;rgb[2]=102; return;}
	if(strcmp("ATC", codon)==0){strcpy(buff, "ile"); rgb[0]=255;rgb[1]=255;rgb[2]=102; return;}
	if(strcmp("ATA", codon)==0){strcpy(buff, "ile"); rgb[0]=255;rgb[1]=255;rgb[2]=102; return;}
	if(strcmp("ATG", codon)==0){strcpy(buff, "met"); rgb[0]=255;rgb[1]=153;rgb[2]=153; return;}
	if(strcmp("GTT", codon)==0){strcpy(buff, "val"); rgb[0]=230; return;}
	if(strcmp("GTC", codon)==0){strcpy(buff, "val"); rgb[0]=230; return;}
	if(strcmp("GTA", codon)==0){strcpy(buff, "val"); rgb[0]=230; return;}
	if(strcmp("GTG", codon)==0){strcpy(buff, "val"); rgb[0]=230; return;}
	if(strcmp("TCT", codon)==0){strcpy(buff, "ser"); rgb[0]=153;rgb[1]=153;rgb[2]=102; return;}
	if(strcmp("TCC", codon)==0){strcpy(buff, "ser"); rgb[0]=153;rgb[1]=153;rgb[2]=102; return;}
	if(strcmp("TCA", codon)==0){strcpy(buff, "ser"); rgb[0]=153;rgb[1]=153;rgb[2]=102; return;}
	if(strcmp("TCG", codon)==0){strcpy(buff, "ser"); rgb[0]=153;rgb[1]=153;rgb[2]=102; return;}
	if(strcmp("CCT", codon)==0){strcpy(buff, "pro"); rgb[0]=255;rgb[1]=230;rgb[2]=204; return;}
	if(strcmp("CCC", codon)==0){strcpy(buff, "pro"); rgb[0]=255;rgb[1]=230;rgb[2]=204; return;}
	if(strcmp("CCA", codon)==0){strcpy(buff, "pro"); rgb[0]=255;rgb[1]=230;rgb[2]=204; return;}
	if(strcmp("CCG", codon)==0){strcpy(buff, "pro"); rgb[0]=255;rgb[1]=230;rgb[2]=204; return;}
	if(strcmp("ACT", codon)==0){strcpy(buff, "thr"); rgb[0]=255;rgb[1]=204;rgb[2]=0; return;}
	if(strcmp("ACC", codon)==0){strcpy(buff, "thr"); rgb[0]=255;rgb[1]=204;rgb[2]=0; return;}
	if(strcmp("ACA", codon)==0){strcpy(buff, "thr"); rgb[0]=255;rgb[1]=204;rgb[2]=0; return;}
	if(strcmp("ACG", codon)==0){strcpy(buff, "thr"); rgb[0]=255;rgb[1]=204;rgb[2]=0; return;}
	if(strcmp("GCT", codon)==0){strcpy(buff, "ala"); rgb[0]=70;rgb[1]=70;rgb[2]=70; return;}
	if(strcmp("GCC", codon)==0){strcpy(buff, "ala"); rgb[0]=70;rgb[1]=70;rgb[2]=70; return;}
	if(strcmp("GCA", codon)==0){strcpy(buff, "ala"); rgb[0]=70;rgb[1]=70;rgb[2]=70; return;}
	if(strcmp("GCG", codon)==0){strcpy(buff, "ala"); rgb[0]=70;rgb[1]=70;rgb[2]=70; return;}
	if(strcmp("TAT", codon)==0){strcpy(buff, "tyr"); rgb[0]=25;rgb[1]=103;rgb[2]=103; return;}
	if(strcmp("TAC", codon)==0){strcpy(buff, "tyr"); rgb[0]=25;rgb[1]=103;rgb[2]=103; return;}
	if(strcmp("TAA", codon)==0){strcpy(buff, "stp"); rgb[0]=255; return;}
	if(strcmp("TAG", codon)==0){strcpy(buff, "stp"); rgb[0]=255; return;}
	if(strcmp("CAT", codon)==0){strcpy(buff, "his"); rgb[0]=51;rgb[1]=153;rgb[2]=255; return;}
	if(strcmp("CAC", codon)==0){strcpy(buff, "his"); rgb[0]=51;rgb[1]=153;rgb[2]=255; return;}
	if(strcmp("CAA", codon)==0){strcpy(buff, "gln"); rgb[0]=153;rgb[1]=255;rgb[2]=102; return;}
	if(strcmp("CAG", codon)==0){strcpy(buff, "gln"); rgb[0]=153;rgb[1]=255;rgb[2]=102; return;}
	if(strcmp("AAT", codon)==0){strcpy(buff, "asn"); rgb[0]=255;rgb[1]=179;rgb[2]=255; return;}
	if(strcmp("AAC", codon)==0){strcpy(buff, "asn"); rgb[0]=255;rgb[1]=179;rgb[2]=255; return;}
	if(strcmp("AAA", codon)==0){strcpy(buff, "lys"); rgb[0]=153;rgb[1]=230;rgb[2]=0; return;}
	if(strcmp("AAG", codon)==0){strcpy(buff, "lys"); rgb[0]=153;rgb[1]=230;rgb[2]=0; return;}
	if(strcmp("GAT", codon)==0){strcpy(buff, "asp"); rgb[2]=60; return;}
	if(strcmp("GAC", codon)==0){strcpy(buff, "asp"); rgb[2]=60; return;}
	if(strcmp("GAA", codon)==0){strcpy(buff, "glu"); rgb[2]=100; return;}
	if(strcmp("GAG", codon)==0){strcpy(buff, "glu"); rgb[2]=100; return;}
	if(strcmp("TGT", codon)==0){strcpy(buff, "cys"); rgb[0]=153;rgb[1]=102;rgb[2]=51; return;}
	if(strcmp("TGC", codon)==0){strcpy(buff, "cys"); rgb[0]=153;rgb[1]=102;rgb[2]=51; return;}
	if(strcmp("TGA", codon)==0){strcpy(buff, "stp"); rgb[0]=255; return;}
	if(strcmp("TGG", codon)==0){strcpy(buff, "trp"); rgb[0]=0;rgb[1]=51;rgb[2]=102; return;}
	if(strcmp("CGT", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("CGC", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("CGA", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("CGG", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("AGT", codon)==0){strcpy(buff, "ser"); rgb[0]=217;rgb[1]=179;rgb[2]=140; return;}
	if(strcmp("AGC", codon)==0){strcpy(buff, "ser"); rgb[0]=217;rgb[1]=179;rgb[2]=140; return;}
	if(strcmp("AGA", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("AGG", codon)==0){strcpy(buff, "arg"); rgb[0]=143;rgb[1]=0;rgb[2]=179; return;}
	if(strcmp("GGT", codon)==0){strcpy(buff, "gly"); rgb[0]=255;rgb[1]=102;rgb[2]=0; return;}
	if(strcmp("GGC", codon)==0){strcpy(buff, "gly"); rgb[0]=255;rgb[1]=102;rgb[2]=0; return;}
	if(strcmp("GGA", codon)==0){strcpy(buff, "gly"); rgb[0]=255;rgb[1]=102;rgb[2]=0; return;}
	if(strcmp("GGG", codon)==0){strcpy(buff, "gly"); rgb[0]=255;rgb[1]=102;rgb[2]=0; return;}
}

int index_ = 0;
int IN_gen = 0;
void write_to_file(FILE *ptr, FILE *af, char *c){
	extern int index_;
	int r, g, b;
	r = g = b = 0;
	if(strchr(c, 'A') != NULL){r = 200;}
	if(strchr(c, 'C') != NULL){g = 200;}
	if(strchr(c, 'G') != NULL){b = 200;}
	if(strchr(c, 'T') != NULL){
		r /= 2;
		g /= 2;
		b /= 2;
	}

	fprintf(ptr, "<th style=\"background-color:rgb(%d, %d, %d);\">%s</th>\n<th> - </th>\n",r,g,b, c);

	char buff[4];
	int rgb[3] = {0};
	extern int IN_gen;
	translt_codon_2_acid(c, buff, rgb);
	if(strcmp(buff, "met") == 0){IN_gen = 1;}
	switch(IN_gen){
		case 0:
			fprintf(af, "<th style=\"background-color:rgb(%d, %d, %d);\">%s</th>\n<th> - </th>\n",170,170,170, buff);
		break;
		case 1:
			fprintf(af, "<th style=\"background-color:rgb(%d, %d, %d);\">%s</th>\n<th> - </th>\n",rgb[0],rgb[1],rgb[2], buff);
		break;
	}
	if(strcmp(buff, "stp") == 0){IN_gen = 0;}
	index_++;

	if(index_ >= 20){
		fprintf(ptr ,"</tr>\n<tr>");
		fprintf(af  ,"</tr>\n<tr>");
		index_ = 0;
	}

}

int codon_index = 0;
void write_codon(char *codon, FILE *file, FILE *af, char c){
	extern int codon_index;
	if(codon_index > 2){

		write_to_file(file, af, codon);

		codon_index = 0;
		codon[0]= '0';
		codon[1]= '0';
		codon[2]= '0';
	}
	codon[codon_index] = c;
	codon_index++;
}

void read_buff(char *buff, FILE *file, FILE *af){
	int pos = 89;
	char *curr = buff;
	char word[71];
	char codon[4];
	curr += pos;
	int sec = 0;
	int milsec = 0;
	while(sscanf(curr, "%70[^\n]%n", word, &pos) != -1){
		curr += pos + 1;

		milsec++;
		if(milsec == 100){milsec=0;sec++;}
		printf("\rpass : %d secend", sec);

		for(int i = 0; i < 70; i++){
			write_codon(codon, file, af, word[i]);
		}
	}
}

int main(){
	char *file = "sequence.fasta";
	char *buff = NULL;

	FILE *fptr = fopen("AND_tran.html", "w");
	fprintf(fptr, "<body><h1 style=\"background-color:powderblue;\">This is a heading</h1><table>");

	FILE *acid_file = fopen("acids.html", "w");
	fprintf(acid_file, "<body><h1 style=\"background-color:powderblue;\">This is a heading</h1><table>");

	int buff_len = read_file(file, &buff);
	read_buff(buff, fptr, acid_file);

	free(buff);
}
