/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <hash_mark.h>

int main(int argc, char ** argv) {

	size_t id;
	double * d1 = (double *)malloc(sizeof(double));
	double * d2 = (double *)malloc(sizeof(double));
	*d1 = 2.0;
	*d2 = 0.0;

	hm_add_table(&id);

	hm_add(id, "d1", d1);

	d2 = (double *)hm_find(id, "d1");

	printf("read value: %lf\n", *d2);

	return 0;
} // main
