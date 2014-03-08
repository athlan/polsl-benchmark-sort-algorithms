#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../common.h"

struct bucketsortListElement {
	record *r;
	struct bucketsortListElement *next;
};

typedef struct bucketsortListElement bucketsortListElement;

int bucket_sort(record **records, const int n) {
	record *A;
	bucketsortListElement **B; // list of buckets
	bucketsortListElement **C; // list of ending element in each bucket
	record *result;
	int i, p;
	int m = 0;
	
	A = *records;
	
	bucketsortListElement *insert_tmp, *insert_new;
	
	// find max primary key
	for(i = 0; i < n; ++i) {
		int key = A[i].primaryKey;
		if(key > m)
			m = key;
	}
	
	result = (record*) malloc(n * sizeof(record*));
	B = (bucketsortListElement**) malloc((m+1) * sizeof(bucketsortListElement*));
	C = (bucketsortListElement**) malloc((m+1) * sizeof(bucketsortListElement*));
	
	for(i = 0; i <= m; ++i) {
		B[i] = NULL;
		C[i] = NULL;
	}
	
	// INSERT
	for(i = 0; i < n; ++i) {
		int key = A[i].primaryKey;
		
		// insert(A[i], B[key], C[key])
		insert_tmp = B[key];
		insert_new = (bucketsortListElement*) malloc(sizeof(bucketsortListElement));
		(*insert_new).r = &A[i];
		(*insert_new).next = insert_tmp;
		B[key] = insert_new;
		
		if(insert_tmp == NULL)
			C[key] = insert_new;
	}
	
	// find first gap
	p = 0; // key_start
	while(B[p] == NULL) {
		p++;
	}
	
	if(p != m) {
		for(i = p+1; i <= m; ++i) {
			if(B[i] != NULL) {
				// join(C[p], B[i], C[i])
				(*C[p]).next = B[i];
				C[p] = C[i];
			}
		}
	}
	
	i = 0;
	insert_tmp = B[p];
	while(insert_tmp != NULL) {
		result[i] = *((*insert_tmp).r);
		
		insert_tmp = (*insert_tmp).next;
		++i;
	}
	
	free(A);
	free(B);
	free(C);
	
	*records = result;
}
