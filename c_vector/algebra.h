#pragma once
#include <stddef.h>
#include <stdlib.h>

/*
 *  fill all fields to create new algebra
 */
struct algebra
{
	size_t size_of_element;
	void* one;
	void* zero;
	void* (*sum)(const void* a, const void* b, void* res);
	void* (*mul)(const void* a, const void* b, void* res);
	void* (*minus)(const void* a, void* res);
};

#define DEF_STD_ALGEBRA_OF(TYPE) \
\
sum_for_std_types_##TYPE(const void* a, const void* b, void* res)\
{\
	*(TYPE *)res = (*(const TYPE*)a + *(const TYPE*)b);\
}\
mul_for_std_types_##TYPE(const void* a, const void* b, void* res)\
{\
	*(TYPE *)res = (*(const TYPE*)a * *(const TYPE*)b);\
}\
minus_for_std_types_##TYPE(const void* a, void* res)\
{\
	*(TYPE *)res = - *(const TYPE*)a;\
}\
\
const TYPE ONE_types_##TYPE = 1;\
const TYPE ZERO_types_##TYPE = 1;\
\
struct algebra TYPE##_algebra =\
{\
	.size_of_element = sizeof(TYPE),\
	.one = (void*)&ONE_types_##TYPE,\
	.zero = (void*)&ZERO_types_##TYPE,\
	.sum = &sum_for_std_types_##TYPE,\
	.mul = &mul_for_std_types_##TYPE,\
	.minus = &minus_for_std_types_##TYPE,\
};\

DEF_STD_ALGEBRA_OF(char)
DEF_STD_ALGEBRA_OF(short)
DEF_STD_ALGEBRA_OF(int)
typedef long long ll;
DEF_STD_ALGEBRA_OF(ll)

DEF_STD_ALGEBRA_OF(float)
DEF_STD_ALGEBRA_OF(double)
