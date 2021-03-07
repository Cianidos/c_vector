#pragma once

#include <assert.h>

#include "alg_vector.h"
#include "c_vector.h"

#define TEST(SECTION, TEST) inline void test_##SECTION##_##TEST(void)
#define EXPECT_EQ(expression1, expression2) assert((expression1) ==  (expression2))
#define EXPECT_FALSE(expression1) assert((expression1) == false)

TEST(c_vector, init)
{
	c_vector* a = vgm.init( 20, sizeof(int));
	EXPECT_EQ(vgm.size(a), 20);
	EXPECT_FALSE(vgm.empty(a));

	c_vector* b = vgm.copy(a);

	EXPECT_EQ(vgm.size(b), 20);
	EXPECT_FALSE(vgm.empty(b));

	vgm.free(a);
	vgm.free(b);
}

TEST(c_vector, at)
{
	c_vector* v = vgm.init(5, sizeof(int));

	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*(int*)vgm.at(v, i) = expected[i];
	}
	for (int i = 0; i < 5; ++i)
	{
		EXPECT_EQ(*(int*)vgm.at(v, i), expected[i]);
	}
	EXPECT_EQ(vgm.at(v, 10), NULL);

	c_vector* b = vgm.copy(v);

	for (int i = 0; i < 5; ++i)
	{
		EXPECT_EQ(*(int*)vgm.at(b, i), expected[i]);
	}
	EXPECT_EQ(vgm.at(b, 10), NULL);

	vgm.free(v);
	vgm.free(b);
}

TEST(c_vector, push_back)
{
	c_vector* v = vgm.init(0, sizeof(int));
	*(int*)vgm.push_back(v) = 2;
	assert(*(int *)vgm.at(v, 0) == 2);
	*(int*)vgm.push_back(v) = 7;
	assert(*(int *)vgm.at(v, 1) == 7);
	*(int *)vgm.push_back(v) = 100;
	assert(*(int *)vgm.at(v, 2) == 100);
	*(int *)vgm.push_back(v) = 1000;
	assert(*(int *)vgm.at(v, 3) == 1000);
	*(int *)vgm.push_back(v) = 10000;
	assert(*(int *)vgm.at(v, 4) == 10000);

	assert(*(int *)vgm.at(v, 0) == 2);
	assert(*(int *)vgm.at(v, 1) == 7);
	assert(*(int *)vgm.at(v, 2) == 100);
	assert(*(int *)vgm.at(v, 3) == 1000);
	assert(*(int *)vgm.at(v, 4) == 10000);

	vgm.free(v);
}

TEST(c_vector, copy)
{
	c_vector* v = vgm.init(5, sizeof(int));
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*(int*)vgm.at(v, i) = expected[i];
	}

	c_vector* v2 = vgm.copy(v);

	assert(vgm.begin(v) != vgm.begin(v2));
	assert(vgm.size(v) == vgm.size(v2));

	for (int i = 0; i < 5; ++i)
	{
		assert(*(int *)vgm.at(v, i) == *(int *)vgm.at(v2, i));
	}

	vgm.free(v);
	vgm.free(v2);
}


TEST(alg_vector, elements_sum_sum_dot)
{
	alg_vector* v = avgm.init(3, &int_algebra);
	alg_vector* v2 = avgm.init(3, &int_algebra);

	*(int*)avgm.at(v, 0) = 5;
	*(int*)avgm.at(v, 1) = 5;
	*(int*)avgm.at(v, 2) = 5;
	int* v_sum = (int*)avgm.elements_sum(v);
	assert(*v_sum == 15);
	
	*(int*)avgm.at(v2, 0) = 1;
	*(int*)avgm.at(v2, 1) = 2;
	*(int*)avgm.at(v2, 2) = 3;
	int* v2_sum = (int*)avgm.elements_sum(v2);
	assert(*v2_sum == 6);

	alg_vector* s_v =  avgm.sum(v, v2);

	assert(*(int*)avgm.at(s_v, 0) == 6);
	assert(*(int*)avgm.at(s_v, 1) == 7);
	assert(*(int*)avgm.at(s_v, 2) == 8);
	
	struct alg_vector* s_v2 = avgm.sum(v2, v);

	assert(*(int*)avgm.at(s_v2, 0) == 6);
	assert(*(int*)avgm.at(s_v2, 1) == 7);
	assert(*(int*)avgm.at(s_v2, 2) == 8);

	int* s_v_sum = (int*)avgm.elements_sum(s_v);
	int* s_v2_sum = (int*)avgm.elements_sum(s_v2);

	assert(*s_v2_sum == *s_v_sum);
	assert(*s_v_sum == 21);

	int* dot = avgm.dot(v, v2);
	int* dot2 = avgm.dot(v2, v);

	assert(*dot == *dot2);
	assert(*dot == 30);

	int* sq_dot = (int*)avgm.dot(v2, v2);
	assert(*sq_dot == 14);

	avgm.free(v);
	avgm.free(v2);
	avgm.free(s_v);
	avgm.free(s_v2);
	free(v_sum);
	free(v2_sum);
	free(s_v_sum);
	free(s_v2_sum);
	free(dot);
	free(dot2);
	free(sq_dot);
}


