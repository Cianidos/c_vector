// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "c_vector.h"

#include <stdlib.h>
#include <string.h>


c_vector*	v_init	(size_t size_of_vector, size_t size_of_element);
void		v_free	(c_vector* v);

int16_t		v_last_err				(void);
const char* v_err_to_string			(int16_t err);
const char* v_last_err_to_string	(int16_t err);

c_vector*	v_copy		(const c_vector* const v);

size_t	v_size			(const c_vector* const v);
bool	v_empty			(const c_vector* const v);

void*	v_at			(c_vector* const v, size_t index);
void*	v_push_back		(c_vector* const v);
void	v_pop_back		(c_vector* const v);
void	v_resize		(c_vector* const v, size_t new_size);
void	v_reserve		(c_vector* const v, size_t new_capacity);
void*	v_begin			(c_vector* const v);
void*	v_end			(c_vector* const v);

const void* v_front		(const c_vector* const v);
const void* v_back		(const c_vector* const v);
const void* v_at_const	(const c_vector* const v, size_t index);


const struct c_vector_global_manager vgm =
{
	.init				= v_init,
	.free				= v_free,
	.last_err			= v_last_err,
	.err_to_string		= v_err_to_string,
	.last_err_to_string	= v_last_err_to_string,
	.copy				= v_copy,
	.size				= v_size,
	.empty				= v_empty,
	.at					= v_at,
	.push_back			= v_push_back,
	.pop_back			= v_pop_back,
	.resize				= v_resize,
	.reserve			= v_reserve,
	.begin				= v_begin,
	.end				= v_end,
	.front				= v_front,
	.back				= v_back,
	.at_const			= v_at_const,
};

struct c_vector_global_error vg_err = { .code = 0 };


int8_t* data_reallocation	(c_vector* v, size_t size);
void	data_extend			(c_vector* const v);
void	data_shrink			(c_vector* const v);


struct c_vector
{
	size_t capacity;
	size_t size;
	size_t element_size;
	int8_t* data;
};


c_vector* v_init(size_t size_of_vector, size_t size_of_element)
{
	c_vector* v = (c_vector*) malloc(sizeof(c_vector));
	if (v == NULL)
	{
		vg_err.code = 2;
		return NULL;
	}
	v->capacity = size_of_vector;
	v->size = size_of_vector;
	v->element_size = size_of_element;
	v->data = (int8_t*) malloc(v->element_size * size_of_vector);
	if (v->data == NULL)
	{
		vg_err.code = 2;
		free(v);
		return NULL;
	}
	return v;
}

void v_free(c_vector* v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return;
	}
	v->size = 0;
	v->capacity = 0;
	v->element_size = 0;

	free(v->data);
	free(v);
}

int16_t v_last_err()
{
	return vg_err.code;
}

const char* v_err_to_string(int16_t err)
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

const char* v_last_err_to_string(int16_t err)
{
	return v_err_to_string(v_last_err());
}

c_vector* v_copy(const c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	c_vector* copy = v_init(v->size, v->element_size);
	if (copy == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	memcpy(copy->data, v->data, v->size * v->element_size);
	return copy;
}

size_t v_size(const c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return 0;
	}
	return v->size;
}

bool v_empty(const c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return 0;
	}
	return v->size == 0;
}

void* v_at(c_vector* const v, size_t index)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	if (index >= v->size)
	{
		vg_err.code = 1;
		return NULL;
	}
	return (void*) &v->data[index * v->element_size];
}

void* v_push_back(c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	while(v->size >= v->capacity)
	{
		data_extend(v);
	}
	v->size += 1;
	return v_at(v, v->size - 1);
}

void v_pop_back(c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return;
	}
	v->size -= 1;
	data_shrink(v);
}

void v_resize(c_vector* const v, size_t new_size)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return;
	}
	if (v->size > new_size)
	{
		v_reserve(v, new_size);
	}
	v->size = new_size;
	data_shrink(v);
}

void v_reserve(c_vector* const v, size_t new_capacity)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return;
	}
	if (v->capacity < new_capacity)
	{
		data_reallocation(v, new_capacity);
	}
}

void* v_begin(c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	return v_at(v, 0);
}

void* v_end(c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	return (void *)((int8_t*)v_at(v, v->size - 1) + v->element_size);
}

const void* v_front(const c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	return v_at_const(v, 0);
}

const void* v_back(const c_vector* const v)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	return v_at_const(v, v->size - 1);
}

const void* v_at_const(const c_vector* const v, size_t index)
{
	if (v == NULL)
	{
		vg_err.code = 3;
		return NULL;
	}
	if (index >= v->size)
	{
		vg_err.code = 1;
		return NULL;
	}
	return (void*) &v->data[index * v->element_size];
}

int8_t* data_reallocation(c_vector* v, size_t size)
{
	int8_t* new_p = (int8_t*)
	realloc((void*)v->data, size * v->element_size);

	if (new_p == NULL)
	{
		vg_err.code = 2;
		return NULL;
	}
	v->data = new_p;
	v->capacity = size;
	return new_p;
}

void data_extend(c_vector* const v)
{
	if (v->capacity == 0) v->capacity = 1;
	data_reallocation(v, v->capacity * 2);
}

void data_shrink(c_vector* const v)
{
	const size_t smaller_capacity = v->capacity / 2;
	if(v->size < smaller_capacity)
	{
		data_reallocation(v, smaller_capacity);
	}
}

