// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "c_string.h"

#include <assert.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *  private declaration
 */

char get_char_c_string(const c_string* const this, const size_t index);
char* at_c_string(c_string* const this, const size_t index);
const char* get_data_c_string(const c_string* const this);

c_string copy_c_string(const c_string* const this);
int compare_with_c_string(const c_string* const this, const c_string* const other);

c_string copy_concat_with_c_string(const c_string* const this, const c_string* const other);
void concat_with_c_string(c_string* const this, const c_string* const other);

void to_lower_case_c_string(c_string* const this);
void to_upper_case_c_string(c_string* const this);

bool empty_c_string(const c_string* const this);

bool contains_ch_c_string(const c_string* const this, const char value);
bool contains_substr_c_string(const c_string* const this, const c_string value);

c_string get_substr_c_string(const c_string* const this, size_t start, size_t stop);
c_string_view get_substr_view_c_string(const c_string* const this, size_t start, size_t stop);


#define ADD_METHOD(OBJ, NAME) OBJ.NAME = NAME##_c_string

struct c_string init_string()
{
	struct c_string res = {._data = NULL, .size = 0};

	ADD_METHOD(res, get_char);
	ADD_METHOD(res, at);
	ADD_METHOD(res, get_data);
	ADD_METHOD(res, copy);
	ADD_METHOD(res, compare_with);
	ADD_METHOD(res, copy_concat_with);
	ADD_METHOD(res, concat_with);
	ADD_METHOD(res, to_lower_case);
	ADD_METHOD(res, to_upper_case);
	ADD_METHOD(res, empty);
	ADD_METHOD(res, contains_ch);
	ADD_METHOD(res, contains_substr);
	ADD_METHOD(res, get_substr);
	ADD_METHOD(res, get_substr_view);
	
	return res;
}

struct c_string init_string_from(const char* c_str)
{
	c_string res = init_string();
	res.size = strlen(c_str);
	res._data = (char*) malloc((res.size + 1) * sizeof(char)); // zero end +1

	//TODO need error check

	memcpy(res._data, c_str, res.size + 1); // zero end +1

	return res;
}


char get_char_c_string(const c_string* const this, const size_t index)
{
	// TODO need error check
	return this->_data[index];
}

char* at_c_string(c_string* const this, const size_t index)
{
	// TODO need error check
	return this->_data + index;
}

const char* get_data_c_string(const c_string* const this)
{
	// TODO need error check
	return this->_data;
}

c_string copy_c_string(const c_string* const this)
{
	c_string res = init_string_from(this->get_data(this));
	return res;
}


int compare_with_c_string(const c_string* const this, const c_string* const other)
{
	return strcmp(this->get_data(this), other->get_data(other));
}

c_string copy_concat_with_c_string(const c_string* const this, const c_string* const other)
{
	c_string res = init_string();
	res.size = this->size + other->size;
	res._data = (char*)malloc((res.size + 1) * sizeof(char)); // zero end + 1
	memcpy(res._data, this->_data, this->size);
	memcpy(res._data + (this->size), other->_data, other->size + 1);
	return res;
}

void concat_with_c_string(c_string* const this, const c_string* const other)
{
	c_string tmp = this->copy_concat_with(this, other);
	free(this->_data);
	*this = tmp;
}

void to_lower_case_c_string(c_string* const this)
{
	for (size_t i = 0; i < this->size; ++i)
	{
		char c = this->get_char(this, i);
		if (c >= 'A' or c <= 'Z')
		{
			*this->at(this, i) = (char)'a' + (char)(c - 'A');
		}
	}
}
void to_upper_case_c_string(c_string* const this)
{
	for (size_t i = 0; i < this->size; ++i)
	{
		char c = this->get_char(this, i);
		if (c >= 'a' or c <= 'z')
		{
			*this->at(this, i) = (char)'A' + (char)(c - 'a');
		}
	}
}

bool empty_c_string(const c_string* const this)
{
	return this->size == 0;
}

bool contains_ch_c_string(const c_string* const this, const char value)
{
	for (size_t i = 0; i < this->size; ++i)
	{
		if (this->get_char(this, i) == value)
		{
			return true;
		}
	}
	return false;
}
bool contains_substr_c_string(const c_string* const this, const c_string value)
{
}

c_string get_substr_c_string(const c_string* const this, size_t start, size_t stop){}
c_string_view get_substr_view_c_string(const c_string* const this, size_t start, size_t stop){}



void test_concat(void)
{
	c_string s1 = init_string_from("Hello ");
	c_string s2 = init_string_from("world");

	c_string s3 = s1.copy_concat_with(&s1, &s2);
	assert(!strcmp("Hello world", s3.get_data(&s3)));

	c_string s4 = init_string_from("");

	c_string s5 = s2.copy_concat_with(&s2, &s4);
	assert(!strcmp(s2.get_data(&s2), s5.get_data(&s5)));

	c_string s6 = s4.copy_concat_with(&s4, &s2);
	assert(!strcmp(s2.get_data(&s2), s6.get_data(&s6)));
}

void test_c_string(void)
{
	test_concat();
}

