// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "c_int_vector.h"


/*
 * private declaration section
 */

int* data_alloc_int_vector
(size_t size);

void data_copy_int_vector
(const struct int_vector* const from, struct int_vector* to);

void data_double_capacity_int_vector
(struct int_vector* const this);


int* at_int_vector
(const struct int_vector* const this, const size_t index);

int push_back_int_vector
(struct int_vector* const this, int value);


struct int_vector* copy_int_vector
(const struct int_vector* const this);

/*
 *private definition section
 */

void data_double_capacity_int_vector
(struct int_vector* const this)
{
	if (this->capacity == 0)
		this->capacity = 1;

	this->capacity *= 2;
	struct int_vector* tmp = init_int_vector_ptr(this->capacity);
	data_copy_int_vector(this, tmp);
	free(this->data);
	this->data = tmp->data;
	free(tmp);
}

int* data_alloc_int_vector
(size_t size)
{
	if (size == 0) return NULL;
	return (int*) malloc(size * sizeof(int));
}

void data_copy_int_vector
(const struct int_vector* const from, struct int_vector* to)
{
	for (size_t i = 0; i < from->size; ++i)
	{
		*to->at(to, i) = *from->at(from, i);
	}	
}

int* at_int_vector
(const struct int_vector * const this, const size_t index)
{
	if (index >= this->size)
	{
		return NULL;
	}
	return &this->data[index];
}

int push_back_int_vector
(struct int_vector* const this, int value)
{
	if (this->size >= this->capacity)
	{
		data_double_capacity_int_vector(this);
	}
	this->data[this->size++] = value;
	return 0;
}


struct int_vector* copy_int_vector
(const struct int_vector* const this)
{
	struct int_vector* res = init_int_vector_ptr(this->capacity);
	res->size = this->size;
	data_copy_int_vector(this, res);
	return res;
}
/*
 * public definition section
 */


struct int_vector init_int_vector
(size_t size)
{
	struct int_vector result;
	result.size = size;
	result.capacity = size;
	result.data = data_alloc_int_vector(size);
	result.at = &at_int_vector;
	result.copy = &copy_int_vector;
	result.push_back = &push_back_int_vector;
	return result;
}

struct int_vector* init_int_vector_ptr
(size_t size)
{
	struct int_vector* res = 
		(struct int_vector*) malloc(sizeof(struct int_vector));
	if(res)
		*res = init_int_vector(size);
	return res;
}

void delete_int_vector
(struct int_vector* vect)
{
	free(vect->data);
	free(vect);
}

/*
 * tests
 */

#include <assert.h>

void test_int_vector_at(void)
{
	struct int_vector v = init_int_vector(5);
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*v.at(&v, i) = expected[i];
	}
	for (int i = 0; i < 5; ++i)
	{
		assert(*v.at(&v, i) == expected[i]);
	}
	assert(v.at(&v, 10) == NULL);
}

void test_int_vector_init(void)
{
	struct int_vector a = init_int_vector(20);
	assert(a.size == 20);
	assert(a.capacity == 20);

	struct int_vector* b = init_int_vector_ptr(20);
	assert(b->size == 20);
	assert(b->capacity == 20);
	free(b);
}

void test_int_vector_push_back(void)
{
	struct int_vector v = init_int_vector(0);
	v.push_back(&v, 2);
	assert(*v.at(&v, 0) == 2);
	v.push_back(&v, 7);
	assert(*v.at(&v, 1) == 7);
	v.push_back(&v, 100);
	assert(*v.at(&v, 2) == 100);
	v.push_back(&v, 1000);
	assert(*v.at(&v, 3) == 1000);
	v.push_back(&v, 10000);
	assert(*v.at(&v, 4) == 10000);

	assert(*v.at(&v, 0) == 2);
	assert(*v.at(&v, 1) == 7);
	assert(*v.at(&v, 2) == 100);
	assert(*v.at(&v, 3) == 1000);
	assert(*v.at(&v, 4) == 10000);
}

void test_int_vector_copy(void)
{
	struct int_vector v = init_int_vector(5);
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*v.at(&v, i) = expected[i];
	}

	struct int_vector* v2 = v.copy(&v);

	assert(v.data != v2->data);
	assert(v.size == v2->size);
	assert(v.capacity == v2->capacity);

	for (int i = 0; i < 5; ++i)
	{
		assert(*v.at(&v, i) == *v2->at(v2, i));
	}
	free(v2);
}

void test_int_vector(void)
{
	test_int_vector_at();
	test_int_vector_init();
	test_int_vector_push_back();
	test_int_vector_copy();
}


