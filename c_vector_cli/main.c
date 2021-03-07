// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "tests.h"
#include <c_vector.h>
#include <stdio.h>
#include <iso646.h>
#include <string.h>

int y_or_n(char c)
{
	if ('a' <= c and c <= 'z')
	{
		return c == 'y';
	}
	if ('A' <= c and c <= 'Z')
	{
		return c == 'Y';
	}
	return -1;
}

const char* error_text = "Sorry, something went wrong";
const char* size_t_format = ((sizeof(size_t) == 4) ? "%u" : "%lu");
int type_of_vector = 0;
size_t dimension = 0;
int init_method = 0;
char want;
int curr_vector = 0;
alg_vector* vec[3];


#define SSCANF(FORMAT, PARAM) \
if(!scanf(FORMAT, PARAM)) { puts(error_text); exit(1); }


#define ANSWER_CHECK(ANSWER, LEFT, RIGHT) \
if(!((LEFT) <= ANSWER and ANSWER <= (RIGHT))) { puts(error_text); exit(1); }
#define PROC(NAME, SIZE) void* (*NAME[SIZE])(void)

void do_nothing(void)
{
}

void int_vector_random(void);
void float_vector_random(void);

void vector_exit(void)
{

	for (int i = 0; i < 3; ++i)
		avgm.free(vec[i]);

	printf("\nGoodbye\n\n");
	exit(0);
}

#define INIT_TEXT_OPERATIONS_FOR_TYPE(TYPE, FORMAT)							\
																			\
void TYPE##_vector_from_keyboard(void);										\
void TYPE##_vector_sum_of_elements(void);									\
void TYPE##_choose_vector_init_method(void);								\
void TYPE##_vector_sum(void);												\
void TYPE##_vector_dot(void);												\
void TYPE##_vector_print(void);												\
																			\
void TYPE##_vector_from_keyboard(void)										\
{																			\
	TYPE a;																	\
	for (size_t i = 0; i < dimension; ++i)									\
	{																		\
		SSCANF(FORMAT, &a);													\
		*(TYPE*)avgm.at(vec[curr_vector], i) = a;							\
	}																		\
}																			\
void TYPE##_vector_sum_of_elements(void)									\
{																			\
	printf("\nvector %d:\n", curr_vector);									\
	printf(FORMAT "\n", *(TYPE*)avgm.elements_sum(vec[curr_vector]));		\
}																			\
void TYPE##_choose_vector_init_method(void)									\
{																			\
	puts("\nChoose vector initialization method:\n 1)Keyboard\n 2)Random");	\
	SSCANF("%d", &init_method);												\
	ANSWER_CHECK(init_method, 1, 2);										\
	PROC(init1, 2) = { &TYPE##_vector_from_keyboard,						\
						&TYPE##_vector_random };							\
	init1[init_method - 1]();												\
}																			\
void TYPE##_vector_sum(void)												\
{																			\
	avgm.free(vec[2]);														\
	vec[2] = avgm.sum(vec[0], vec[1]);										\
	curr_vector = 2;														\
	TYPE##_vector_print();													\
}																			\
void TYPE##_vector_dot(void)												\
{																			\
	avgm.free(vec[2]);														\
	vec[2] = avgm.dot(vec[0], vec[1]);										\
	curr_vector = 2;														\
	TYPE##_vector_print();													\
}																			\
void TYPE##_vector_print(void)												\
{																			\
	for(size_t i = 0; i < avgm.dimension(vec[curr_vector]); ++i)			\
	{																		\
		printf(FORMAT, *(TYPE*)avgm.at(vec[curr_vector], i));				\
		printf(" ");														\
	}																		\
	puts("");																\
}																			\
void TYPE##_main_cli_choose()												\
{																			\
	for (int i = 0; i < 3; ++i)												\
		vec[i] = avgm.init(													\
			dimension,														\
			(type_of_vector == 1) ? &int_algebra : &float_algebra);			\
	TYPE##_choose_vector_init_method();										\
	int b_next1;															\
	puts("\nWhat do you want next?\n 1)sum of elements\n "					\
			"2)make second vector");										\
	SSCANF("%d", &b_next1);													\
	ANSWER_CHECK(b_next1, 1, 2);											\
	PROC(next1, 2) = { &TYPE##_vector_sum_of_elements,						\
						&TYPE##_choose_vector_init_method };				\
	curr_vector = b_next1 - 1;												\
	next1[curr_vector]();													\
	if (b_next1 == 2)														\
	{																		\
		int b_next2;														\
		puts("\nWhat next?\n 1)sum\n 2)dot");								\
		SSCANF("%d", &b_next2);												\
		ANSWER_CHECK(b_next2, 1, 2);										\
		PROC(next2, 2) = { &TYPE##_vector_sum, &TYPE##_vector_dot };		\
		next2[b_next2 - 1]();												\
																			\
		int want_to_print = 1;												\
		while (want_to_print != 4)											\
		{																	\
			puts("\nWant to print?\n 1)first vector\n 2)second vector\n" 	\
					" 3)result vector\n 4)no");								\
			SSCANF("%d", &want_to_print);									\
			ANSWER_CHECK(want_to_print, 1, 4);								\
			PROC(print1, 3) = { &TYPE##_vector_print, &do_nothing };		\
			curr_vector = want_to_print - 1;								\
			print1[(want_to_print == 4) ? 1 : 0]();							\
		}																	\
	}																		\
																			\
	int want_to_exit = 1;													\
	puts("\nWant to ?\n 1)exit\n 2)repeat\n");								\
	SSCANF("%d", &want_to_exit);											\
	ANSWER_CHECK(want_to_exit, 1, 2);										\
	PROC(print1, 3) = { &vector_exit, &do_nothing };						\
	print1[want_to_exit - 1]();												\
}																		

INIT_TEXT_OPERATIONS_FOR_TYPE(int, "%d");
INIT_TEXT_OPERATIONS_FOR_TYPE(float, "%f");

void int_vector_random(void)
{
	puts("\nEnter two numbers - left and right bounds for random initialization");
	int l, r;
	SSCANF("%d", &l);
	SSCANF("%d", &r);
	for (size_t i = 0; i < dimension; ++i)
	{
		const int a = (rand() % (r - l)) + l;
		*(int*)avgm.at(vec[curr_vector], i) = a;
	}
	int_vector_print();
}

void float_vector_random(void)
{
	puts("\nEnter two numbers - left and right bounds for random initialization");
	float l, r;
	SSCANF("%f", &l);
	SSCANF("%f", &r);
	for (size_t i = 0; i < dimension; ++i)
	{
		const float a = ((float)rand() / (float)RAND_MAX) * (r - l) + l;
		*(float*)avgm.at(vec[curr_vector], i) = a;
	}
	float_vector_print();
}


void console_ui(void)
{
	PROC(myf, 3);

	puts("Do you want to make vector? y/n: ");
	SSCANF("%c", &want);
	if (!y_or_n(want))
		vector_exit();

	while (true)
	{
		puts("\nChoose type of elements of vector:\n 1)int\n 2)float");
		SSCANF("%d", &type_of_vector);
		ANSWER_CHECK(type_of_vector, 1, 2);

		printf("\nEnter dimension of vector: ");
		SSCANF(size_t_format, &dimension);
		ANSWER_CHECK(dimension, 0, SIZE_MAX);


		if (type_of_vector == 1)
		{
			int_main_cli_choose();
		}
		else
		{
			float_main_cli_choose();
		}
		for (int i = 0; i < 3; ++i)
			avgm.free(vec[i]);
	}
}
int main()
{
	test_c_vector_push_back();
	test_alg_vector_elements_sum_sum_dot();
	test_c_vector_at();
	test_c_vector_init();
	test_c_vector_copy();

	console_ui();

	return 0;
}
