/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <hash_mark.h>

int main(int argc, char ** argv) {

	size_t t0, t1;
	double * d0 = (double *)malloc(sizeof(double));
	double * d1 = (double *)malloc(sizeof(double));
	double * f = NULL;
	*d0 = 2.0;
	*d1 = 45.0;

	// add tables
	hm_add_table(&t0);
	hm_add_table(&t1);

	printf("t0: %d\n", (int64_t)t0);
	printf("t1: %d\n", (int64_t)t1);

	// add entries
	hm_add(t0, "d0", d0);
	hm_add(t0, "d1", d1);

	f = (double *)hm_find(t0, "d0");
	printf("found value(d0): %lf\n", *f);

	f = (double *)hm_find(t0, "d1");
	printf("found value(d1): %lf\n", *f);

	hm_remove(t0, "d0", 1);

	hm_remove_table(t0, 1);

	return 0;
} // main
