#include "stack.h"
#include <gtest.h>

TEST(Stack, positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(3));
}

TEST(Stack, negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-3));
}

TEST(Stack, zero_length)
{
	ASSERT_ANY_THROW(Stack<int> st(0));
}

TEST(Stack, show_stack_top)
{
	Stack<int> st(3);
	st.push(5);
	EXPECT_EQ(5, st.show_top());
	EXPECT_EQ(false, st.Empty());
}

TEST(Stack, can’t_show_empty_stack_top)
{
	Stack<int> st(3);
	int this_top;
	EXPECT_EQ(true, st.Empty());
	ASSERT_ANY_THROW(this_top = st.show_top());
}

TEST(Stack, push_to_stack)
{
	Stack<int> st(3);
	st.push(5);
	EXPECT_EQ(5, st.show_top());
}

TEST(Stack, push_to_full_stack)
{
	Stack<int> st(1);
	st.push(1);
	EXPECT_EQ(true, st.Full());
	st.push(2);
	EXPECT_EQ(2, st.show_top());
}

TEST(Stack, pop_from_stack)
{
	Stack<int> st(2);
	st.push(1);
	st.push(2);
	EXPECT_EQ(2, st.pop());
	EXPECT_EQ(1, st.show_top());
	EXPECT_EQ(1, st.pop());
	EXPECT_EQ(true, st.Empty());
}

TEST(Stack, can’t_pop_from_empty_stack)
{
	Stack<int> st(3);
	int this_top;
	EXPECT_EQ(true, st.Empty());
	ASSERT_ANY_THROW(this_top = st.pop());
}

TEST(Stack, check_is_empty)
{
	Stack<int> st(3);
	EXPECT_EQ(true, st.Empty());
	st.push(1);
	EXPECT_EQ(false, st.Empty());
}

TEST(Stack, check_is_full)
{
	Stack<int> st(1);
	EXPECT_EQ(false, st.Full());
	st.push(1);
	EXPECT_EQ(true, st.Full());
}

TEST(Stack, get_current_stack_size)
{
	Stack<int> st(3);
	EXPECT_EQ(0, st.current_size());
	st.push(1);
	EXPECT_EQ(1, st.current_size());
}

TEST(Stack, clear_stack)
{
	Stack<int> st(3);
	st.push(1);
	EXPECT_EQ(false, st.Empty());
	st.clear();
	EXPECT_EQ(true, st.Empty());
}