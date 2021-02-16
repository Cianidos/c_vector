#pragma once
#include <stddef.h>
#include "c_any_vector.h"
#include "algebra.h"


struct alg_vector
{
	struct algebra alg;
	struct any_vector vector;

	void* (*elements_sum)
	(const struct alg_vector * const this);

	struct alg_vector* (*sum)
	(const struct alg_vector * const this, const struct alg_vector * const other);

	void* (*dot)
	(const struct alg_vector * const this, const struct alg_vector * const other);

	struct alg_vector* (*copy)
	(const struct alg_vector * const this);
};

/*
 *  public declaration 
 */

struct alg_vector init_alg_vector(size_t dimension, struct algebra algebra);
void delete_alg_vector(struct alg_vector vect);

struct alg_vector* init_alg_vector_ptr(size_t dimension, struct algebra algebra);
void delete_alg_vector_ptr(struct alg_vector* vect);
