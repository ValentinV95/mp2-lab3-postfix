#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(3));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-3));
}

TEST(Stack, throws_when_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(Stack<int> st(0));
}

TEST(Stack, can_show_stack_top)
{
	Stack<int> st(3);
	st.push(5);
	EXPECT_EQ(5, st.show_top());
	EXPECT_EQ(false, st.isEmpty());
}

TEST(Stack, can_not_show_empty_stack_top)
{
	Stack<int> st(3);
	int this_top;
	EXPECT_EQ(true, st.isEmpty());
	ASSERT_ANY_THROW(this_top = st.show_top());
}

TEST(Stack, can_push_element_to_stack)
{
	Stack<int> st(3);
	st.push(5);
	EXPECT_EQ(5, st.show_top());
}

TEST(Stack, can_push_element_to_full_stack)
{
	Stack<int> st(1);
	st.push(1);
	EXPECT_EQ(true, st.isFull());
	st.push(2);
	EXPECT_EQ(2, st.show_top());
}

TEST(Stack, can_pop_element_from_stack)
{
	Stack<int> st(2);
	st.push(1);
	st.push(2);
	EXPECT_EQ(2, st.pop());
	EXPECT_EQ(1, st.show_top());
	EXPECT_EQ(1, st.pop());
	EXPECT_EQ(true, st.isEmpty());
}

TEST(Stack, can_not_pop_element_from_empty_stack)
{
	Stack<int> st(3);
	int this_top;
	EXPECT_EQ(true, st.isEmpty());
	ASSERT_ANY_THROW(this_top = st.pop());
}

TEST(Stack, can_check_stack_is_empty)
{
	Stack<int> st(3);
	EXPECT_EQ(true, st.isEmpty());
	st.push(1);
	EXPECT_EQ(false, st.isEmpty());
}

TEST(Stack, can_check_stack_is_full)
{
	Stack<int> st(1);
	EXPECT_EQ(false, st.isFull());
	st.push(1);
	EXPECT_EQ(true, st.isFull());
}

TEST(Stack, can_get_current_stack_size)
{
	Stack<int> st(3);
	EXPECT_EQ(0, st.current_size());
	st.push(1);
	EXPECT_EQ(1, st.current_size());
}

TEST(Stack, can_clear_stack)
{
	Stack<int> st(3);
	st.push(1);
	EXPECT_EQ(false, st.isEmpty());
	st.clear();
	EXPECT_EQ(true, st.isEmpty());
}