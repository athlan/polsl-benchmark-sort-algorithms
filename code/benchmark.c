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

int main(int argc, char **argv) {
	char *buffer;
	size_t buffer_size = 255;
	int n, i, k, tmp;
	record *tab, *tab_copy;
	clock_t t_start, t_end;
	
	buffer = (char*) malloc(255 * sizeof(char));
	
	n = 0;
	i = 0;
	while(getline(&buffer, &buffer_size, stdin) > 0) {
		tmp = atoi(buffer);
		
		if(i == 0) {
			n = tmp;
			tab = (record*) malloc(n * sizeof(record));
		}
		else {
			tab[i-1].primaryKey = tmp;
		}
		
		++i;
	}
	
	for(k = 1; k < argc; ++k) {
		record *tab_copy = (record*) malloc(n * sizeof(record));
		for(i = 0; i < n; ++i) {
			tab_copy[i].primaryKey = tab[i].primaryKey;
		}
		
		if(strcmp("counting", argv[k]) == 0) {
			t_start = clock();
			
			counting_sort(&tab_copy, n);
			
			t_end = clock();
			printf("%f\t%s\n", (float)(t_end - t_start) / CLOCKS_PER_SEC, argv[k]);
		}
		else if(strcmp("bucket", argv[k]) == 0) {
			t_start = clock();
			
			bucket_sort(&tab_copy, n);
			
			t_end = clock();
			printf("%f\t%s\n", (float)(t_end - t_start) / CLOCKS_PER_SEC, argv[k]);
		}
		
		/*printf("Sorted:\n");
		for(i = 0; i < n; ++i) {
			printf("%d: %d\n", i, tab_copy[i].primaryKey);
		}*/
		free(tab_copy);
	}
}
/*
record* make_copy(const record *tab, int n) {
	int i;
	
	return tab_copy;
}
*/