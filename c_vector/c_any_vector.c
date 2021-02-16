#include "c_any_vector.h"

/*
 * private declaration section
 */

void copy_one_element
(void* from, void* to, const size_t size_of_element);

int8_t* data_alloc_any_vector
(size_t size_of_data, size_t size_of_element);

void data_copy_any_vector
(const struct any_vector* const from, struct any_vector* to);

void data_double_capacity_any_vector
(struct any_vector* const this);


void* at_any_vector
(const struct any_vector* const this, const size_t index);

void* push_back_any_vector
(struct any_vector* const this);


struct any_vector* copy_any_vector
(const struct any_vector* const this);

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

void data_double_capacity_any_vector
(struct any_vector* const this)
{
	if (this->capacity == 0)
		this->capacity = 1;

	this->capacity *= 2;
	struct any_vector* tmp = init_any_vector_ptr(this->capacity, this->_element_size);
	data_copy_any_vector(this, tmp);
	free(this->data);
	this->data = tmp->data;
	free(tmp);
}

int8_t* data_alloc_any_vector
(size_t size_of_data, size_t size_of_element)
{
	if (size_of_data == 0) return NULL;
	return (int8_t*) malloc(size_of_data * size_of_element);
}

void data_copy_any_vector
(const struct any_vector* const from, struct any_vector* to)
{
	for (size_t i = 0; i < from->size; ++i)
	{
		copy_one_element(from->at(from, i), to->at(to, i), from->_element_size);
	}	
}

void* at_any_vector
(const struct any_vector * const this, const size_t index)
{
	if (index >= this->size)
	{
		return NULL;
	}
	return &this->data[index * this->_element_size];
}

void* push_back_any_vector
(struct any_vector* const this)
{
	if (this->size >= this->capacity)
	{
		data_double_capacity_any_vector(this);
	}
	++(this->size);
	return this->at(this, this->size - 1);
}


struct any_vector* copy_any_vector
(const struct any_vector* const this)
{
	struct any_vector* res = init_any_vector_ptr(this->capacity, this->_element_size);
	res->size = this->size;
	data_copy_any_vector(this, res);
	return res;
}
/*
 * public definition section
 */


struct any_vector init_any_vector
(size_t size_of_vector, size_t size_of_one_element)
{
	struct any_vector result;
	result.size = size_of_vector;
	result._element_size = size_of_one_element;
	result.capacity = size_of_vector;
	result.data = 
		data_alloc_any_vector(
			result.capacity, 
			result._element_size
		);
	result.at = &at_any_vector;
	result.copy = &copy_any_vector;
	result.push_back = &push_back_any_vector;
	return result;
}

struct any_vector* init_any_vector_ptr
(size_t size_of_vector, size_t size_of_one_element)
{
	struct any_vector* res = 
		(struct any_vector*) malloc(sizeof(struct any_vector));
	*res = init_any_vector(size_of_vector, size_of_one_element);
	return res;
}

void delete_any_vector
(struct any_vector* vect)
{
	free(vect->data);
	free(vect);
}


/*
 * tests
 */

#include <assert.h>


void test_any_vector_at(void)
{
	struct any_vector v = init_any_vector(5, sizeof(int));
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
}

void test_any_vector_init(void)
{
	struct any_vector a = init_any_vector(20,sizeof(int));
	assert(a.size == 20);
	assert(a.capacity == 20);

	struct any_vector* b = init_any_vector_ptr(20, sizeof(int));
	assert(b->size == 20);
	assert(b->capacity == 20);
}

void test_any_vector_push_back(void)
{
	struct any_vector v = init_any_vector(0, sizeof(int));
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
}

void test_any_vector_copy(void)
{
	struct any_vector v = init_any_vector(5, sizeof(int));
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*(int*)v.at(&v, i) = expected[i];
	}

	struct any_vector* v2 = v.copy(&v);

	assert(v.data != v2->data);
	assert(v.size == v2->size);
	assert(v.capacity == v2->capacity);

	for (int i = 0; i < 5; ++i)
	{
		assert(*(int *)v.at(&v, i) == *(int *)v2->at(v2, i));
	}
}

void test_any_vector(void)
{
	test_any_vector_at();
	test_any_vector_init();
	test_any_vector_push_back();
	test_any_vector_copy();
}
