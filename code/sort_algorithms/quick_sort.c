#include <stdlib.h>
#include "../common.h"

int quick_sort_compare(const void * a, const void * b)
{
    int _a = (*(record*)a).primaryKey;
    int _b = (*(record*)b).primaryKey;
    if(_a < _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}

int quick_sort(record **records, const int n) {
	record *tab;
	tab = *records;
	
	qsort(tab, n, sizeof(record), quick_sort_compare);
	
	*records = tab;
}
