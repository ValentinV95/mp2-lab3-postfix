#include "stack.h"
#include <gtest.h>


TEST(Stack, can_push_element)
{
	Stack<double> st;
	ASSERT_NO_THROW(st.push(5.3));
	EXPECT_EQ(5.3, st.checkTop());
}

TEST(Stack, can_pop_element)
{
	Stack<double> st;
	double res = 0.0;
	st.push(5.3);
	ASSERT_NO_THROW(res = st.pop());
	EXPECT_EQ(5.3, res);
}


TEST(Stack, can_check_top_without_removal)
{
	Stack<double> st;
	double res = 0.0;
	st.push((double)5.3);
	ASSERT_NO_THROW(res = st.checkTop());
	EXPECT_EQ(5.3, res);
}

TEST(Stack, can_check_is_empty)
{
	Stack<double> st;
	bool empty = false;
	ASSERT_NO_THROW(empty = st.isEmpty());
	EXPECT_EQ(true, empty);
}

TEST(Stack, can_get_amount_of_elements)
{
	Stack<double> st(5);
	int amount = 0;
	for (size_t i = 0; i < 3; i++)
	{
		st.push(i);
	}
	ASSERT_NO_THROW(amount = st.get_size());
	EXPECT_EQ(3, amount);
}

TEST(Stack, can_clear_stack)
{
	Stack<double> st(5);
	for (size_t i = 0; i < 3; i++)
	{
		st.push(i);
	}
	ASSERT_NO_THROW(st.clear());
	EXPECT_EQ(true, st.isEmpty());
}

TEST(Stack, can_reallocate_memory_if_full)
{
	Stack<double> st(3);
	for (size_t i = 0; i < 3; i++)
	{
		st.push(i);
	}
	ASSERT_NO_THROW(st.push(1));
	EXPECT_EQ(4, st.get_size());
}

TEST(Stack, cant_get_negative_size_as_parameter)
{
	ASSERT_ANY_THROW(Stack<double> st(-1));
}

TEST(Stack, cant_pop_from_empty_stack)
{
	Stack<double> st;
	st.clear();
	ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, cant_checkTop_if_empty_stack)
{
	Stack<double> st;
	st.clear();
	ASSERT_ANY_THROW(st.checkTop());
}

TEST(Stack, pop_remove_top_element)
{
	Stack<double> st(2);
	st.push(1);
	st.push(2);
	st.pop();
	EXPECT_EQ(1, st.checkTop());
}