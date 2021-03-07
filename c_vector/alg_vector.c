// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "alg_vector.h"


#include <assert.h>
#include <string.h>


alg_vector*	av_init		(size_t dimension, algebra* alg);
void		av_free		(alg_vector* av);

int16_t		av_last_err				(void);
const char*	av_err_to_string		(int16_t err);
const char*	av_last_err_to_string	(int16_t err);

size_t		av_dimension	(const alg_vector* const av);
void*		av_at			(const alg_vector* const av, size_t index);

void*		av_elements_sum	(const alg_vector* const av);
void*		av_dot			(const alg_vector* const av, const alg_vector* const other);
alg_vector*	av_sum			(const alg_vector* const av, const alg_vector* const other);

alg_vector*	av_copy			(const alg_vector* const av);


struct algebraic_vector_global_manager avgm =
{
	.init				= av_init,
	.free				= av_free,

	.last_err			= av_last_err,
	.err_to_string		= av_err_to_string,
	.last_err_to_string	= av_last_err_to_string,

	.dimension			= av_dimension,
	.at					= av_at,
	.elements_sum		= av_elements_sum,
	.dot				= av_dot ,
	.sum				= av_sum ,
	.copy				= av_copy,
};

struct algebraic_vector_global_error avg_err = { .code = 0 };

struct alg_vector
{
	algebra* alg;
	c_vector* vec;
};


alg_vector* av_init(size_t dimension, algebra* alg)
{
	alg_vector* av = (alg_vector*) malloc(sizeof(alg_vector));

	if (av == NULL)
	{
		avg_err.code = 2;
		return NULL;
	}

	NEW_C_VECTOR(v, dimension, alg->size_of_element);

	if (v == NULL)
	{
		avg_err.code = 2;
		free(av);
		return NULL;
	}
	av->vec = v;
	av->alg = alg;
	return av;
}

void av_free(alg_vector* av)
{
	if(av == NULL)
	{
		avg_err.code = 3;
		return;
	}
	vgm.free(av->vec);
	av->alg = NULL;
	free(av);
}

int16_t av_last_err()
{
	return avg_err.code;
}

const char* av_err_to_string(int16_t err)
{
	switch (err)
	{
	case 0:
		return "No errors";
	case 1:
		return "Out of range access";
	case 2:
		return "Unsuccessful allocation of memory";
	case 3:
		return "NULL vector received";
	default:;
	}
	return "Incorrect error code";
}

const char* av_last_err_to_string(int16_t err)
{
	return av_err_to_string(av_last_err());
}

size_t av_dimension(const alg_vector* const av)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return 0;
	}
	return vgm.size(av->vec);
}

void* av_at(const alg_vector* const av, size_t index)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	if (index >= vgm.size(av->vec))
	{
		avg_err.code = 1;
		return NULL;
	}
	return vgm.at(av->vec, index);
}

void* av_elements_sum(const alg_vector* const av)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	const c_vector* v = av->vec;

	void* res = malloc(av->alg->size_of_element);
	if (res == NULL)
	{
		avg_err.code = 2;
		return NULL;
	}

	if (vgm.size(v) == 1)
	{
		memcpy(res, vgm.at_const(v, 0), av->alg->size_of_element);
	}
	else
	{
		av->alg->sum(vgm.at_const(v, 0), vgm.at_const(v, 1), res);
		for (size_t i = 2; i < vgm.size(v); ++i)
		{
			av->alg->sum(vgm.at_const(v, i), res, res);
		}
	}
	return res;
}

void* av_dot(const alg_vector* const av, const alg_vector* const other)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	if (other == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	assert(vgm.size(av->vec) == vgm.size(other->vec));
	alg_vector* res = avgm.init(vgm.size(av->vec), av->alg);

	if (res == NULL)
	{
		avg_err.code = 2;
		return NULL;
	}

	const c_vector* t = av->vec, * o = other->vec;
	c_vector* r = res->vec;

	for (size_t i = 0; i < vgm.size(t); ++i)
	{
		av->alg->mul(vgm.at_const(t, i), vgm.at_const(o, i), vgm.at(r, i));
	}

	void* real_res = av_elements_sum(res);

	av_free(res);
	return real_res;
}

alg_vector* av_sum(const alg_vector* const av, const alg_vector* const other)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	if (other == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	assert(vgm.size(av->vec) == vgm.size(other->vec));
	alg_vector* res = avgm.init(vgm.size(av->vec), av->alg);

	if (res == NULL)
	{
		avg_err.code = 2;
		return NULL;
	}

	const c_vector* t = av->vec, * o = other->vec;
	c_vector* r = res->vec;

	for (size_t i = 0; i < vgm.size(t); ++i)
	{
		av->alg->sum(vgm.at_const(t, i), vgm.at_const(o, i), vgm.at(r, i));
	}
	return res;
}

alg_vector* av_copy(const alg_vector* const av)
{
	if (av == NULL)
	{
		avg_err.code = 3;
		return NULL;
	}
	struct alg_vector* res = avgm.init(0, av->alg);
	if (res == NULL)
	{
		avg_err.code = 2;
		return NULL;
	}
	vgm.free(av->vec);
	res->vec = vgm.copy(av->vec);
	return res;
}

