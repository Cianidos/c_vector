#include "alg_vector.h"


#include <assert.h>
#include <string.h>


/*
 *  private declaration
 */

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
	result.vector = init_any_vector(dimension, algebra.size_of_element);
	ADD_METHOD(result, elements_sum);
	ADD_METHOD(result, sum);
	ADD_METHOD(result, dot);
	ADD_METHOD(result, copy);
	return result;
}

void delete_alg_vector(struct alg_vector vect)
{
	delete_any_vector(vect.vector);
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
	delete_any_vector(vect->vector);
	free(vect);
}


/*
 *  private definition
 */

void* elements_sum_alg_vector
(const struct alg_vector* const this)
{
	const struct any_vector* v = &this->vector;

	void* res = malloc(v->_element_size);

	if (v->size == 1)
	{
		memcpy(res, v->at(v, 0), v->_element_size);
	} else
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
	struct any_vector* t = &this->vector, * o = &other->vector, * r = &res->vector;

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
	struct any_vector* t = &this->vector, * o = &other->vector, * r = &res->vector;

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
	delete_any_vector(this->vector);
	struct any_vector* tmp = this->vector.copy(&this->vector);
	res->vector = *tmp;
	free(tmp);
	return res;
}

