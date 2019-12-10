#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitmatrix.h"
#include "bitmatrix-internals.h"

/* Testing bm_popcount_r() and _c() */

int main()
{
	srand((unsigned)time(NULL));
	int i, cmp;		//counter
	int len = 80;
	char *msg = "Testing bm_popcount_r() and _c()";
	char *status[] = { "[PASS]", "[FAIL]" };
	int dots = len - strlen(msg) - 6;	/* 6 is the length of pass/fail string */
	printf("%s", msg);
	for (i = 0; i < dots; i++)
		printf(".");
	int retval = 0;
	struct bitmatrix *input = bm_new(10, 10);
	unsigned int counter_r[10] = {0};
	unsigned int counter_c[10] = {0};
	int x, y;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 10; y++) {
			if (rand() % 2) {
				BITSET(input, x, y);
				counter_r[x]++;
				counter_c[y]++;
			}
		}
	}
	int tmp;
	unsigned int total_r = 0;
	unsigned int total_c = 0;
	for (x = 0; x < 10; x++) {
		tmp = bm_popcount_r(input, x);
		total_r += tmp;
		if (tmp != counter_r[x]) {
			retval = 1;
			goto ret;
		}
	}
	for (y = 0;y  < 10; y++) {
		tmp = bm_popcount_c(input, y);
		total_c += tmp;
		if (tmp != counter_c[y]) {
			retval = 1;
			goto ret;
		}
	}
	if (total_r != total_c) {
		retval = 1;
		goto ret;
	}
ret:
	bm_del(&input);
	printf("%s\n", status[retval]);
	return retval;
}
