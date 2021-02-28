// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "c_int_vector.h"
#include "c_macro_vector.h"
#include "c_void_vector.h"
#include "alg_vector.h"
#include "functional_extention_for_void_vector.h"
#include "c_string.h"


int main(void)
{
	
	test_int_vector();
	test_macro_vector();
	test_void_vector();
	test_alg_vector();
	test_functional();
	test_c_string();

	return 0;
}