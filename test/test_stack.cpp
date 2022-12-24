// тесты для стека

#include "stack.h"
#include <gtest.h>


TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> st);
}

TEST(Stack, create_stack_is_empty)
{
	Stack<int> st;
	EXPECT_EQ(st.IsEmpty(), true);
}

TEST(Stack, can_push_elem_to_stack)
{
	Stack<int> st;
	st.Push(1);
	EXPECT_EQ(st.IsEmpty(), false);
	EXPECT_EQ(st.Pop(), 1);
}

TEST(Stack, stack_is_not_empty_after_push_elem)
{
	Stack<int> st;
	st.Push(1);
	EXPECT_EQ(st.IsEmpty(), false);
}

TEST(Stack, push_change_stack_size)
{
	Stack<int> st;
	EXPECT_EQ(st.GetSize(), 0);
	st.Push(1);
	EXPECT_EQ(st.GetSize(), 1);
	st.Push(2);
	EXPECT_EQ(st.GetSize(), 2);
}

TEST(Stack, can_clear_stack)
{
	Stack<int> st;
	st.Push(1);
	st.Push(2);
	EXPECT_EQ(st.IsEmpty(), false);
	st.Clear();
	EXPECT_EQ(st.IsEmpty(), true);
}

TEST(Stack, can_pop_elem)
{
	Stack<int> st;
	st.Push(10);
	EXPECT_EQ(st.Pop(), 10);
}

TEST(Stack, pop_change_stack_size)
{
	Stack<int> st;
	st.Push(10);
	st.Push(10);
	int size = st.GetSize();
	st.Pop();
	EXPECT_EQ(st.GetSize(), size - 1);
}

TEST(Stack, can_show_top_elem)
{
	Stack<int> st;
	st.Push(10);
	EXPECT_EQ(st.Top(), 10);
}

TEST(Stack, top_dont_change_stack_size)
{
	Stack<int> st;
	st.Push(10);
	st.Push(10);
	int size = st.GetSize();
	st.Top();
	EXPECT_EQ(st.GetSize(), size);
}