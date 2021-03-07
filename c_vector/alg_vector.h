#pragma once
#include <stddef.h>
#include "c_vector.h"
#include "algebra.h"

struct alg_vector;
typedef struct alg_vector alg_vector;

struct algebraic_vector_global_manager
{
	alg_vector* (*init)			(size_t dimension, algebra* alg);
	void		(*free)			(alg_vector* av);

	int16_t		(*last_err)				(void);
	const char*	(*err_to_string)		(int16_t err);
	const char*	(*last_err_to_string)	(int16_t err);

	size_t		(*dimension)	(const alg_vector* const av);
	void*		(*at)			(const alg_vector* const av, size_t index);

	void*		(*elements_sum)	(const alg_vector* const av);
	void*		(*dot)			(const alg_vector* const av, const alg_vector* const other);
	alg_vector*	(*sum)			(const alg_vector* const av, const alg_vector* const other);

	alg_vector*	(*copy)			(const alg_vector* const av);
};
extern struct algebraic_vector_global_manager avgm;


//	code 0 "No errors";
//	code 1 "Out of range access";
//	code 2 "Unsuccessful allocation of memory";
//	code 3 "NULL alg_vector received";
struct algebraic_vector_global_error 
{
	//  0 by default
	int16_t code;
};
extern struct algebraic_vector_global_error avg_err;

