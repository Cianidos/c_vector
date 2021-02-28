// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "functional_extention_for_void_vector.h"


#include <assert.h>
#include <string.h>

struct void_vector* where(const struct void_vector* const vector, int(* predicate)(void*))
{
	struct void_vector* res = init_void_vector_ptr(0, vector->_element_size);
	if (!res)
		return res;
	for (size_t i = 0; i < vector->size; ++i)
	{
		if (predicate(vector->at(vector, i)))
		{
			memcpy(res->push_back(res), vector->at(vector, i), vector->_element_size);
		}
	}
	return res;
}

struct void_vector* map(const struct void_vector* const vector, void*(* producer)(void*), size_t size_of_produced_type)
{
	struct void_vector* res = init_void_vector_ptr(0, size_of_produced_type);
	if (!res)
		return res;
	for (size_t i = 0; i < vector->size; ++i)
	{
		void* value = producer(vector->at(vector, i));
		memcpy(res->push_back(res), value, size_of_produced_type);
		free(value);
	}
	return res;
}

void* reduce(const struct void_vector* const vector, void*(* reducer)(void*, void*), void* init_value)
{
	void* res = init_value;
	if (!res)
		return res;

	for (size_t i = 0; i < vector->size; ++i)
	{
		res = reducer(vector->at(vector, i), res);
	}
	return res;
}

/*
 *  tests
 */
int example_pred(void* str)
{
	char* st = *(char**) str;
	return strchr(st, 'd');
}

void* cat_strs(void* from, void* to)
{
	char* t = *(char**)to;
	char* f = *(char**)from;

	strcat(t, f);

	return to;
}

void* len(void* s)
{
	int* res = malloc(sizeof(int));
	*res = strlen(*(char**)s);
	return res;
}

void* plus(void* l, void* r)
{
	*(int*)r += *(int*)l;
	return r;
}


void test_functional(void)
{
	NEW_VECTOR_PTR_OF(v, char**, 0);
	char* src[] = { "hello", "world", "aaaaa", "bbbbb", "abcde" };
	
	*(char**)v->push_back(v) = src[0];
	*(char**)v->push_back(v) = src[1];
	*(char**)v->push_back(v) = src[2];
	*(char**)v->push_back(v) = src[3];
	*(char**)v->push_back(v) = src[4];

	struct void_vector* only_with_d = where(v, example_pred);
	char* buff = calloc(50, 1);
	buff[0] = '\0';
	
	char** cat = reduce(only_with_d, cat_strs, &buff);
	assert(!strcmp(*cat, "worldabcde"));

	struct void_vector* lengthses = map(only_with_d, len, sizeof(int));
	int summm = 0;
	reduce(lengthses, plus, &summm);

	assert(summm == 10);
}

