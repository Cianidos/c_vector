// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "algebra.h"

#define DEF_STD_ALGEBRA_OF(TYPE)				\
												\
void sum_for_std_types_##TYPE					\
(const void* a, const void* b, void* res)		\
{												\
	*((TYPE *)res) =							\
	(*((const TYPE*)a) + *((const TYPE*)b));	\
}												\
void mul_for_std_types_##TYPE					\
(const void* a, const void* b, void* res)		\
{												\
	*((TYPE *)res) =							\
	(*((const TYPE*)a) * *((const TYPE*)b));	\
}												\
void minus_for_std_types_##TYPE					\
(const void* a, void* res)						\
{												\
	*((TYPE *)res) =							\
	(-(*(const TYPE*)a));						\
}												\
bool less_for_std_type_##TYPE					\
(const void* a, const void* b)					\
{												\
	return *((TYPE *)a) < *((TYPE *)b);			\
}												\
												\
const TYPE ONE_types_##TYPE = (TYPE) 1;			\
const TYPE ZERO_types_##TYPE = (TYPE) 0;		\
												\
struct algebra TYPE##_algebra =					\
{												\
	.size_of_element = sizeof(TYPE),			\
	.one = (const void*)&ONE_types_##TYPE,		\
	.zero = (const void*)&ZERO_types_##TYPE,	\
	.sum = &sum_for_std_types_##TYPE,			\
	.mul = &mul_for_std_types_##TYPE,			\
	.minus = &minus_for_std_types_##TYPE,		\
	.less = &less_for_std_type_##TYPE			\
};												

DEF_STD_ALGEBRA_OF(char)
DEF_STD_ALGEBRA_OF(short)
DEF_STD_ALGEBRA_OF(int)
typedef long long ll;
DEF_STD_ALGEBRA_OF(ll)

DEF_STD_ALGEBRA_OF(float)
DEF_STD_ALGEBRA_OF(double)
