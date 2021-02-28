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


#define DECL_STD_ALGEBRA_OF(TYPE) \
\
void sum_for_std_types_##TYPE(const void* a, const void* b, void* res);\
void mul_for_std_types_##TYPE(const void* a, const void* b, void* res);\
void minus_for_std_types_##TYPE(const void* a, void* res);\
\
extern const TYPE ONE_types_##TYPE;\
extern const TYPE ZERO_types_##TYPE;\
\
extern struct algebra TYPE##_algebra; 


DECL_STD_ALGEBRA_OF(char)
DECL_STD_ALGEBRA_OF(short)
DECL_STD_ALGEBRA_OF(int)
typedef long long ll;
DECL_STD_ALGEBRA_OF(ll)

DECL_STD_ALGEBRA_OF(float)
DECL_STD_ALGEBRA_OF(double)
