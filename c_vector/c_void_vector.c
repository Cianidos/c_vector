// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "c_void_vector.h"

/*
 * private declaration section
 */

void copy_one_element
(void* from, void* to, const size_t size_of_element);

int8_t* data_alloc_void_vector
(const size_t size_of_data, const size_t size_of_element);

void data_copy_void_vector
(const struct void_vector* const from, struct void_vector* to);

void data_double_capacity_void_vector
(struct void_vector* const this);


void* at_void_vector
(const struct void_vector* const this, const size_t index);

void* push_back_void_vector
(struct void_vector* const this);

void reserve_void_vector
(struct void_vector* const this, const size_t new_size);


struct void_vector* copy_void_vector
(const struct void_vector* const this);


void* begin_void_vector
(const struct void_vector* const this);

void* end_void_vector
(const struct void_vector* const this);

void* front_void_vector
(const struct void_vector* const this);

void* back_void_vector
(const struct void_vector* const this);


/*
 *private definition section
 */

void copy_one_element
(void* from, void* to, const size_t size_of_element)
{
	int8_t* a = (int8_t*)from;
	int8_t* b = (int8_t*)to;
	for (size_t j = 0; j < size_of_element; ++j)
	{
		b[j] = a[j];
	}
}

void data_double_capacity_void_vector
(struct void_vector* const this)
{
	if (this->_capacity == 0)
		this->_capacity = 1;

	this->reserve(this, this->_capacity * 2);
}

int8_t* data_alloc_void_vector
(const size_t size_of_data, const size_t size_of_element)
{
	if (size_of_data == 0) return NULL;
	return (int8_t*) malloc(size_of_data * size_of_element);
}

void data_copy_void_vector
(const struct void_vector* const from, struct void_vector* to)
{
	for (size_t i = 0; i < from->size; ++i)
	{
		copy_one_element(from->at(from, i), to->at(to, i), from->_element_size);
	}	
}

void* at_void_vector
(const struct void_vector * const this, const size_t index)
{
	if (index >= this->size)
	{
		return NULL;
	}
	return &this->data[index * this->_element_size];
}

void* push_back_void_vector
(struct void_vector* const this)
{
	if (this->size >= this->_capacity)
	{
		data_double_capacity_void_vector(this);
	}
	++(this->size);
	return this->at(this, this->size - 1);
}

void reserve_void_vector
(struct void_vector* const this, const size_t new_size)
{
	if (new_size > this->_capacity)
	{
		this->_capacity = new_size;
		void* tmp = realloc((void *)this->data, this->_capacity * this->_element_size);
		if (tmp)
			this->data = (int8_t*)tmp;
	}
}

void* begin_void_vector(const struct void_vector* const this)
{
	return this->begin(this);
}

void* end_void_vector(const struct void_vector* const this)
{
	return ((char*)this->back(this) + this->_element_size);
}

void* front_void_vector(const struct void_vector* const this)
{
	if (this->data)
		return this->data;
	return NULL;
}

void* back_void_vector(const struct void_vector* const this)
{
	if (this->data)
		return this->at(this, this->size - 1);
	return NULL;
}


struct void_vector* copy_void_vector
(const struct void_vector* const this)
{
	struct void_vector* res = init_void_vector_ptr(this->_capacity, this->_element_size);
	res->size = this->size;
	data_copy_void_vector(this, res);
	return res;
}


/*
 * public definition section
 */


#define ADD_METHOD(OBJ, NAME) OBJ.NAME = NAME##_##void_vector

struct void_vector init_void_vector
(size_t size_of_vector, size_t size_of_one_element)
{
	struct void_vector result;
	result.size = size_of_vector;
	result._element_size = size_of_one_element;
	result._capacity = size_of_vector;
	result.data = 
		data_alloc_void_vector(
			result._capacity, 
			result._element_size
		);

	ADD_METHOD(result, at);
	ADD_METHOD(result, push_back);
	ADD_METHOD(result, copy);
	ADD_METHOD(result, reserve);
	ADD_METHOD(result, begin);
	ADD_METHOD(result, end);
	ADD_METHOD(result, front);
	ADD_METHOD(result, back);

	return result;
}

struct void_vector* init_void_vector_ptr
(size_t size_of_vector, size_t size_of_one_element)
{
	struct void_vector* res = 
		(struct void_vector*) malloc(sizeof(struct void_vector));
	if (res != NULL)
		*res = init_void_vector(size_of_vector, size_of_one_element);
	return res;
}

void delete_void_vector
(struct void_vector vect)
{
	free(vect.data);
}

void delete_void_vector_ptr
(struct void_vector* vect)
{
	free(vect->data);
	free(vect);
}


/*
 * tests
 */

#ifndef NDEBUG

#include <assert.h>

void test_void_vector_at(void)
{
	struct void_vector v = init_void_vector(5, sizeof(int));
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*(int*)v.at(&v, i) = expected[i];
	}
	for (int i = 0; i < 5; ++i)
	{
		assert(*(int*)v.at(&v, i) == expected[i]);
	}
	assert(v.at(&v, 10) == NULL);

	delete_void_vector(v);
}

void test_void_vector_init(void)
{
	struct void_vector a = init_void_vector(20,sizeof(int));
	assert(a.size == 20);
	assert(a._capacity == 20);

	struct void_vector* b = init_void_vector_ptr(20, sizeof(int));
	assert(b->size == 20);
	assert(b->_capacity == 20);

	delete_void_vector(a);
	delete_void_vector_ptr(b);
}

void test_void_vector_push_back(void)
{
	struct void_vector v = init_void_vector(0, sizeof(int));
	*(int*)v.push_back(&v) = 2;
	assert(*(int *)v.at(&v, 0) == 2);
	*(int*)v.push_back(&v) = 7;
	assert(*(int *)v.at(&v, 1) == 7);
	*(int *)v.push_back(&v) = 100;
	assert(*(int *)v.at(&v, 2) == 100);
	*(int *)v.push_back(&v) = 1000;
	assert(*(int *)v.at(&v, 3) == 1000);
	*(int *)v.push_back(&v) = 10000;
	assert(*(int *)v.at(&v, 4) == 10000);

	assert(*(int *)v.at(&v, 0) == 2);
	assert(*(int *)v.at(&v, 1) == 7);
	assert(*(int *)v.at(&v, 2) == 100);
	assert(*(int *)v.at(&v, 3) == 1000);
	assert(*(int *)v.at(&v, 4) == 10000);

	delete_void_vector(v);
}

void test_void_vector_copy(void)
{
	struct void_vector v = init_void_vector(5, sizeof(int));
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*(int*)v.at(&v, i) = expected[i];
	}

	struct void_vector* v2 = v.copy(&v);

	assert(v.data != v2->data);
	assert(v.size == v2->size);
	assert(v._capacity == v2->_capacity);

	for (int i = 0; i < 5; ++i)
	{
		assert(*(int *)v.at(&v, i) == *(int *)v2->at(v2, i));
	}

	delete_void_vector(v);
	delete_void_vector_ptr(v2);
}

void test_void_vector(void)
{
	test_void_vector_at();
	test_void_vector_init();
	test_void_vector_push_back();
	test_void_vector_copy();
}
#else
void test_void_vector(void)
{
}
#endif

