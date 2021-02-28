// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "alg_vector.h"

#include <assert.h>
#include <string.h>


/*
 *  private declaration
 */

void* at_alg_vector
(const struct alg_vector* const this, size_t index);

void* elements_sum_alg_vector
(const struct alg_vector* const this);

struct alg_vector* sum_alg_vector
(const struct alg_vector* const this, const struct alg_vector* const other);

void* dot_alg_vector
(const struct alg_vector* const this, const struct alg_vector* const other);

struct alg_vector* copy_alg_vector
(const struct alg_vector* const this);

/*
 *  public definition
 */

#define ADD_METHOD(OBJ, NAME) OBJ.NAME = NAME##_alg_vector


struct alg_vector init_alg_vector(size_t dimension, struct algebra algebra)
{
	struct alg_vector result;
	result.alg = algebra;
	result.vector = init_void_vector(dimension, algebra.size_of_element);
	ADD_METHOD(result, at);
	ADD_METHOD(result, elements_sum);
	ADD_METHOD(result, sum);
	ADD_METHOD(result, dot);
	ADD_METHOD(result, copy);
	return result;
}

void delete_alg_vector(struct alg_vector vect)
{
	delete_void_vector(vect.vector);
}

struct alg_vector* init_alg_vector_ptr(size_t dimension, struct algebra algebra)
{
	struct alg_vector* res =
		(struct alg_vector*)malloc(sizeof(struct alg_vector));
	if (res)
		*res = init_alg_vector(dimension, algebra);
	return res;
}


void delete_alg_vector_ptr(struct alg_vector* vect)
{
	delete_void_vector(vect->vector);
	free(vect);
}


/*
 *  private definition
 */

void* at_alg_vector(const struct alg_vector* const this, size_t index)
{
	return this->vector.at(&this->vector, index);
}

void* elements_sum_alg_vector
(const struct alg_vector* const this)
{
	const struct void_vector* v = &this->vector;

	void* res = malloc(v->_element_size);
	if (!res)
		return res;

	if (v->size == 1)
	{
		memcpy(res, v->at(v, 0), v->_element_size);
	}
	else
	{
		this->alg.sum(v->at(v, 0), v->at(v, 1), res);
		for (size_t i = 2; i < v->size; ++i)
		{
			this->alg.sum(v->at(v, i), res, res);
		}
	}

	return res;
}

struct alg_vector* sum_alg_vector
(const struct alg_vector* const this, const struct alg_vector* const other)
{
	assert(this->vector.size == other->vector.size);
	struct alg_vector* res = init_alg_vector_ptr(this->vector.size, this->alg);
	if (!res)
		return res;
	const struct void_vector* t = &this->vector, * o = &other->vector;
	struct void_vector* r = &res->vector;

	for (size_t i = 0; i < t->size; ++i)
	{
		this->alg.sum(t->at(t, i), o->at(o, i), r->at(r, i));
	}
	return res;
}

void* dot_alg_vector
(const struct alg_vector* const this, const struct alg_vector* const other)
{
	assert(this->vector.size == other->vector.size);
	struct alg_vector* res = init_alg_vector_ptr(this->vector.size, this->alg);
	if (!res)
		return res;
	const struct void_vector* t = &this->vector, * o = &other->vector;
	struct void_vector* r = &res->vector;

	for (size_t i = 0; i < t->size; ++i)
	{
		this->alg.mul(t->at(t, i), o->at(o, i), r->at(r, i));
	}

	void* real_res = res->elements_sum(res);
	delete_alg_vector_ptr(res);
	return real_res;
}

struct alg_vector* copy_alg_vector
(const struct alg_vector* const this)
{
	struct alg_vector* res = init_alg_vector_ptr(0, this->alg);
	if (!res)
		return res;
	delete_void_vector(this->vector);
	struct void_vector* tmp = this->vector.copy(&this->vector);
	res->vector = *tmp;
	free(tmp);
	return res;
}


/*
 *  tests
 */
#ifndef NDEBUB
#include <assert.h>

void test_element_sum_dot(void)
{
	struct alg_vector v = init_alg_vector(3, int_algebra);
	struct alg_vector v2 = init_alg_vector(3, int_algebra);

	*(int*)v.at(&v, 0) = 5;
	*(int*)v.at(&v, 1) = 5;
	*(int*)v.at(&v, 2) = 5;
	int* v_sum = (int*)v.elements_sum(&v);
	assert(*v_sum == 15);
	
	*(int*)v2.at(&v2, 0) = 1;
	*(int*)v2.at(&v2, 1) = 2;
	*(int*)v2.at(&v2, 2) = 3;
	int* v2_sum = (int*)v2.elements_sum(&v2);
	assert(*v2_sum == 6);

	struct alg_vector* s_v =  v.sum(&v, &v2);

	assert(*(int*)s_v->at(s_v, 0) == 6);
	assert(*(int*)s_v->at(s_v, 1) == 7);
	assert(*(int*)s_v->at(s_v, 2) == 8);
	
	struct alg_vector* s_v2 =  v2.sum(&v2, &v);

	assert(*(int*)s_v2->at(s_v2, 0) == 6);
	assert(*(int*)s_v2->at(s_v2, 1) == 7);
	assert(*(int*)s_v2->at(s_v2, 2) == 8);

	int* s_v_sum = (int*)s_v->elements_sum(s_v);
	int* s_v2_sum = (int*)s_v2->elements_sum(s_v2);

	assert(*s_v2_sum == *s_v_sum);
	assert(*s_v_sum == 21);

	int* dot = v.dot(&v, &v2);
	int* dot2 = v2.dot(&v2, &v);

	assert(*dot == *dot2);
	assert(*dot == 30);

	int* sq_dot = (int*)v2.dot(&v2, &v2);
	assert(*sq_dot == 14);

	delete_alg_vector_ptr(s_v);
	delete_alg_vector_ptr(s_v2);
	free(s_v_sum);
	free(s_v2_sum);
	free(dot);
	free(dot2);
	free(sq_dot);
}


void test_alg_vector(void)
{
	test_element_sum_dot();
}
#else
void test_alg_vector(void)
{
}
#endif

