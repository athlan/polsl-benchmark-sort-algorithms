#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "sort_algorithms/counting_sort.h"
#include "sort_algorithms/bucket_sort.h"

int getline(char **lineptr, size_t *n, FILE *stream)
{
	static char line[256];
	char *ptr;
	unsigned int len;
	
	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if (ferror (stream))
		return -1;

	if (feof(stream))
		return -1;
     
	fgets(line,256,stream);

	ptr = strchr(line,'\n');   
	if (ptr)
		*ptr = '\0';

	len = strlen(line);
	
	if ((len+1) < 256)
	{
		ptr = realloc(*lineptr, 256);
		if (ptr == NULL)
			return(-1);
		*lineptr = ptr;
		*n = 256;
   }

   strcpy(*lineptr,line); 
   return(len);
}

// signatures
float benchmark_bucket_sort(const record *tab, int n, int iterations);
float benchmark_counting_sort(const record *tab, int n, int iterations);

int main(int argc, char **argv) {
	char *buffer;
	size_t buffer_size = 255;
	int n, i, k;
	record *tab;
	
	int iterations = atoi(argv[1]);
	n = atoi(argv[2]);
	tab = (record*) malloc(n * sizeof(record));
	
	// get line by line
	i = 0;
	buffer = (char*) malloc(255 * sizeof(char));
	while(getline(&buffer, &buffer_size, stdin) > 0) {
		tab[i].primaryKey = atoi(buffer);
		++i;
	}
	free(buffer);
	
	printf("%d;", iterations);
	printf("%d;", n);
	
	for(k = 2; k < argc; ++k) {
		record *tab_copy = (record*) malloc(n * sizeof(record));
		for(i = 0; i < n; ++i) {
			tab_copy[i].primaryKey = tab[i].primaryKey;
		}
		
		if(strcmp("counting", argv[k]) == 0) {
			float total_time = benchmark_counting_sort(tab, n, iterations);
			printf("%f;", total_time, argv[k]);
		}
		else if(strcmp("bucket", argv[k]) == 0) {
			float total_time = benchmark_bucket_sort(tab, n, iterations);
			printf("%f;", total_time, argv[k]);
		}
		
		/*printf("Sorted:\n");
		for(i = 0; i < n; ++i) {
			printf("%d: %d\n", i, tab_copy[i].primaryKey);
		}*/
	}
	
	free(tab);
}

float benchmark_bucket_sort(const record *tab, int n, int iterations) {
	float total_time = 0;
	clock_t t_start, t_end;
	
	record *tab_copy;
	int i, k;
	
	for(k = 0; k < iterations; ++k) {
		record *tab_copy = (record*) malloc(n * sizeof(record));
		for(i = 0; i < n; ++i) {
			tab_copy[i].primaryKey = tab[i].primaryKey;
		}
		
		t_start = clock();
		bucket_sort(&tab_copy, n);
		t_end = clock();
		
		total_time += ((float)(t_end - t_start) / CLOCKS_PER_SEC);
		free(tab_copy);
	}
	return total_time;
}

float benchmark_counting_sort(const record *tab, int n, int iterations) {
	float total_time = 0;
	clock_t t_start, t_end;
	
	record *tab_copy;
	int i, k;
	
	for(k = 0; k < iterations; ++k) {
		record *tab_copy = (record*) malloc(n * sizeof(record));
		for(i = 0; i < n; ++i) {
			tab_copy[i].primaryKey = tab[i].primaryKey;
		}
		
		t_start = clock();
		counting_sort(&tab_copy, n);
		t_end = clock();
		
		total_time += ((float)(t_end - t_start) / CLOCKS_PER_SEC);
		free(tab_copy);
	}
	return total_time;
}

/*
record* make_copy(const record *tab, int n) {
	int i;
	
	return tab_copy;
}
*/