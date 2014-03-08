#include <stdlib.h>
#include "../common.h"

int counting_sort(record **records, const int n) {
	int i;
	int m = 0;
	
	record *A, *B;
	int *C;
	
	A = *records;
	
	// find max primary key
	for(i = 0; i < n; ++i) {
		int key = A[i].primaryKey;
		if(key > m)
			m = key;
	}
	
	B = (record*) malloc(n * sizeof(record));
	C = (int*) malloc(m * sizeof(int));
	
	// make counting table zero
	for(i = 0; i <= m; ++i) {
		C[i] = 0;
	}
	
	// count, how many times one key apperas in index
	for(i = 0; i < n; ++i) {
		int key = A[i].primaryKey;
		C[key] = C[key] + 1;
	}
	
	// the main power of algorithm
	// count, how many lower items is befora current index
	for(i = 1; i <= m; ++i) {
		C[i] = C[i] + C[i - 1];
	}
	
	// insert items from A to B
	// by counted index appears in C
	for(i = n-1; i >= 0; --i) {
		int key = A[i].primaryKey;
		B[C[key]-1] = A[i];
		C[key] = C[key] - 1;
	}
	
	free(C);
	
	// A is no longer needed
	// new copy of sorted elements is now stored under B
	free(*records);
	
	// change pointer
	*records = B;
}
