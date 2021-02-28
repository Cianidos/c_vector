#include "tests.h"
#include <c_vector.h>
#include <stdio.h>
#include <complex.h>

int main()
{
	test_c_vector_push_back();
	test_alg_vector_elements_sum_sum_dot();
	test_c_vector_at();
	test_c_vector_init();
	test_c_vector_copy();

	return 0;
}
