/*----------------------------------------------------------------------------*
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <hash_mark.h>

int main(int argc, char ** argv) {

	size_t t0, t1;
	double * d0 = (double *)malloc(sizeof(double));
	double * d1 = (double *)malloc(sizeof(double));
	double * d2 = (double *)malloc(sizeof(double));
	double * d3 = (double *)malloc(sizeof(double));
	double * f = NULL;
	extern int32_t hm_result;

	*d0 = 2.0;
	*d1 = 45.0;

	hm_set_property(hm_free_data);
	//hm_set_property(hm_exit_on_error);

	// add tables
	hm_add_table(&t0);
	hm_add_table(&t1);

	printf("t0: %d\n", (int64_t)t0);

	printf("t1: %d\n", (int64_t)t1);

	// add entries
	hm_add(t0, "d0", d0);
	printf("result: %"PRIi32"\n", hm_result);
	hm_add(t0, "d0", d0);
	printf("result: %"PRIi32"\n", hm_result);
	
	if(hm_result != hm_success) {
		printf("failed\n");
	} // if

	hm_add(t0, "d1", d1);
	hm_add(t1, "d2", d2);
	hm_add(t1, "d3", d3);

	f = (double *)hm_find(t0, "d0");
	printf("result: %"PRIi32"\n", hm_result);
	printf("found value(d0): %lf\n", *f);

	f = (double *)hm_find(t0, "d1");
	printf("found value(d1): %lf\n", *f);

#if 0
	hm_remove(t0, "d0", 1);
	hm_remove(t0, "d1", 1);
	hm_remove(t1, "d2", 1);
	hm_remove(t1, "d3", 1);

	hm_remove_table(t0, 1);
	hm_remove_table(t1, 1);
#endif

	return 0;
} // main
