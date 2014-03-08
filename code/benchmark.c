#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "sort_algorithms/counting_sort.h"
#include "sort_algorithms/bucket_sort.h"

int main(int argc, char *argv) {
	int i;
	int n = 10;
	record *tab = malloc(n * sizeof(record));
	
	tab[0].primaryKey = 10;
	tab[1].primaryKey = 2;
	tab[2].primaryKey = 4;
	tab[3].primaryKey = 60;
	tab[4].primaryKey = 30;
	tab[5].primaryKey = 24;
	tab[6].primaryKey = 25;
	tab[7].primaryKey = 66;
	tab[8].primaryKey = 5;
	tab[9].primaryKey = 22;
	
	// sort
	//counting_sort(&tab, n);
	bucket_sort(&tab, n);
	
	printf("Sorted:\n");
	for(i = 0; i < n; ++i) {
		printf("%d: %d\n", i, tab[i].primaryKey);
	}
	printf("End.\n");
}
