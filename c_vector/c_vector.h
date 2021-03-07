#pragma once
#include <stdbool.h>
#include <stdint.h>


struct c_vector;
typedef struct c_vector c_vector;

struct c_vector_global_manager 
{
	c_vector*	(*init)		(size_t size_of_vector, size_t size_of_element);
	void		(*free)		(c_vector* v);

	int16_t		(*last_err)				(void);
	const char*	(*err_to_string)		(int16_t err);
	const char*	(*last_err_to_string)	(int16_t err);

	c_vector*	(*copy)	(const c_vector* const v);

	size_t(*size)		(const c_vector* const v);
	bool  (*empty)		(const c_vector* const v);
	
	void* (*at)			(c_vector* const v, size_t index);
	void* (*push_back)	(c_vector* const v);
	void  (*pop_back)	(c_vector* const v);
	void  (*resize)		(c_vector* const v, size_t new_size);
	void  (*reserve)	(c_vector* const v, size_t new_capacity);
	void* (*begin)		(c_vector* const v);
	void* (*end)		(c_vector* const v);

	const void* (*front)	(const c_vector* const v);
	const void* (*back)		(const c_vector* const v);
	const void* (*at_const)	(const c_vector* const v, size_t index);
};
extern const struct c_vector_global_manager vgm;

//	code 0 "No errors";
//	code 1 "Out of range access";
//	code 2 "Unsuccessful allocation of memory";
//	code 3 "NULL vector received";
struct c_vector_global_error 
{
	//  0 by default
	int16_t code;
};

extern struct c_vector_global_error vg_err;

#define NEW_C_VECTOR(NAME, SIZE, TYPE_SIZE) c_vector* NAME = vgm.init((SIZE), (TYPE_SIZE))
