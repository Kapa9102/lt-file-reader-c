#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_LEN 2
#define MAX_PER_LINE 256

/* Definitions (structs) */

typedef struct line_t line_t;
typedef struct file_t file_t;

struct line_t{
	int b_size;		      
	char data[MAX_PER_LINE];
};

struct file_t{
	int b_size, capacity, count;  
	struct line_t* lines;         
};

void load_file (file_t* tt, const char* path); // load file into file_t 

/* Implementations */

void load_file (file_t* tt, const char* path)
{
	char c;
	int i=0;
	if (!tt) {
		perror ("empty file_t");
		exit(1);
	}
	if (!path) {
		perror ("fake path");
		exit(1);
	}
	tt -> lines = (line_t *) malloc (sizeof(line_t) * INIT_LEN);
	tt -> capacity = INIT_LEN;
	tt -> b_size= 0;
	tt -> count = 0;
	FILE* fptr = fopen (path, "r");
	if (!fptr) {
		fprintf(stderr, "cannot open file at path : %s", path);
		exit(1);
	}
	while ((c = fgetc(fptr)) != EOF) {
		if (tt -> count >= tt -> capacity) { 
			tt -> capacity *= 2;
			tt -> lines = realloc (tt->lines, tt->capacity * sizeof(line_t));
			if (! tt -> lines ) {
				perror ("realloc: error");
				exit (1);
			}
		}
		tt -> lines [tt -> count].data[i++] = (c == '\n') ? '\0':c;
		tt -> lines [tt -> count].b_size++;
		if (c == '\n') {
			tt -> lines [tt -> count].b_size -= 1;
			tt -> count ++;                         
			i=0;
		} 
		tt -> b_size ++;
	}
	fclose (fptr);
	return ;
}

int main (void)
{
	file_t mate;                      
        load_file (&mate, "nvs8.tex"); 	// load file into mate

	for (int i=0; i<mate.count; i++) 
		printf ("<%d>:<%s>\n", mate.lines[i].b_size ,mate.lines[i].data);

	printf("capacity : %d\n", mate.capacity);
	printf("count    : %d\n", mate.count);
	printf("b_size   : %d\n", mate.b_size);
	free (mate.lines);
}








