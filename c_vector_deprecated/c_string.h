#pragma once
#include <stdbool.h>
#include <string.h>

/*
 *	string owning struct
 */

struct c_string;
typedef struct c_string c_string;

struct c_string_view;
typedef struct c_string_view c_string_view;

struct c_string
{
	char* _data;

	size_t size;

	char (*get_char)(const c_string* const this, const size_t index);
	char* (*at)(c_string* const this, const size_t index);
	const char* (*get_data)(const c_string* const this);

	c_string(*copy)(const c_string* const this);
	int (*compare_with)(const c_string* const this, const c_string* const other);
	
	c_string(*copy_concat_with)(const c_string* const this, const c_string* const other);
	void (*concat_with)(c_string* const this, const c_string* const other);

	void (*to_lower_case)(c_string* const this);
	void (*to_upper_case)(c_string* const this);

	bool (*empty)(const c_string* const this);

	bool (*contains_ch)(const c_string* const this, const char value);
	bool (*contains_substr)(const c_string* const this, const c_string value);
	
	c_string(*get_substr)(const c_string* const this, size_t start, size_t stop);
	c_string_view(*get_substr_view)(const c_string* const this, size_t start, size_t stop);
};

struct c_string_view
{
	char* _begin, * _end;
};

struct c_string init_string();
struct c_string init_string_from(const char* c_str);


void test_c_string();

