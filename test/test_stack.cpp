// тесты для стека
#include "stack.h"
#include <gtest.h>

TEST(TStack,can_create_stack)
{
	ASSERT_NO_THROW(Stack<double>(2));
}

TEST(TStack,can_create_copy)
{
	Stack<double> st1;
	ASSERT_NO_THROW(Stack<double>st2(st1));
}

TEST(TStack,copied_stack_has_its_own_memory)
{
	Stack<int> st1;
	st1.push(1);

	Stack<int> st2(st1);
	st2.clear();
	st2.push(2);
	EXPECT_EQ(st1.head(), 1);
	EXPECT_EQ(st2.head(), 2);
}

TEST(TStack, can_get_size)
{
	Stack<int> st1;
	st1.push(1);
	EXPECT_EQ(st1.getSize(), 1);
	st1.push(2);
	EXPECT_EQ(st1.getSize(), 2);


	Stack<int> st2(5);
	EXPECT_EQ(st2.getSize(),0);
}

TEST(TStack,can_push_element)
{
	Stack<int> st;
	st.push(10);
	EXPECT_EQ(st.head(), 10);
	st.push(3);
	EXPECT_EQ(st.head(), 3);
}

TEST(TStack, cant_pop_from_empty_stack)
{
	Stack<int> st(3);
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, cant_get_head_from_empty_stack)
{
	Stack<int> st(3);
	ASSERT_ANY_THROW(st.head());
}

TEST(TStack, pop_removes_head_element)
{
	Stack<int> st(2);
	st.push(5);
	st.push(10);
	st.pop();
	EXPECT_EQ(st.head(), 5);
}

TEST(TStack, head_return_top_element)
{
	Stack<int> st;
	st.push(5);
	EXPECT_EQ(st.head(),5);
}

TEST(TStack,is_empty_works_correctly)
{
	Stack<int> st(3);
	EXPECT_EQ(st.isEmpty(), true);
	st.push(2);
	EXPECT_EQ(st.isEmpty(), false);
	st.push(2);
	EXPECT_EQ(st.isEmpty(), false);
}

TEST(TStack, clear_removes_all_elements)
{
	Stack<int> st(3);
	st.push(1);
	st.push(2);
	st.push(3);
	st.clear();
	EXPECT_EQ(st.isEmpty(), true);
}