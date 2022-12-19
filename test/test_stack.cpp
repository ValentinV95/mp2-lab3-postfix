// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<double>());
}

TEST(TStack, can_create_copy)
{
	TStack<double> st;
	ASSERT_NO_THROW(TStack<double>stCopy(st));
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<double> st;
	st.push(7.7);
	TStack<double>stCopy(st);
	st.push(9.9);
	EXPECT_EQ(stCopy.top(), 7.7);
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<double> st;
	st.push(7.7);
	ASSERT_NO_THROW(st = st);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	TStack<double> st;
	TStack<double> st1;
	st.push(2.0);
	st1.push(3.0);
	ASSERT_NO_THROW(st1 = st);
}

TEST(TStack, can_get_size)
{
	TStack<double> st;
	st.push(7.7);
	EXPECT_EQ(st.size(), 1);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	TStack<double> st;
	TStack<double> st1;
	st.push(3.0);
	st.push(2.0);
	st1.push(3.0);
	ASSERT_NO_THROW(st1 = st);
}

TEST(TStack, assign_operator_change_stack_size)
{
	TStack<double> st;
	TStack<double> st1;
	st.push(3.0);
	st.push(2.0);
	st1.push(3.0);
	st1 = st;
	EXPECT_EQ(st1.size(),2);
}

TEST(TStack, assigned_stack_is_equal_to_source_one)
{
	TStack<double> st;
	TStack<double> st1;
	st.push(3.0);
	st.push(2.0);
	st1.push(3.0);
	st1 = st;
	EXPECT_EQ(st.top(), st1.top());
}

TEST(TStack, can_push_element)
{
	TStack<double> st;
	st.push(3.0);
	EXPECT_EQ(st.top(), 3.0);
	st.push(2.0);
	EXPECT_EQ(st.top(), 2.0);
}

TEST(TStack, cant_pop_from_empty_stack )
{
	TStack<double> st;
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, cant_get_top_from_empty_stack)
{
	TStack<double> st;
	ASSERT_ANY_THROW(st.top());
}

TEST(TStack, pop_removes_top_element)
{
	TStack<double> st;
	st.push(3.0);
	st.push(2.0);
	st.pop();
	EXPECT_EQ(st.top(), 3.0);
}

TEST(TStack, top_return_top_element)
{
	TStack<double> st;
	st.push(3.0);
	EXPECT_EQ(st.top(), 3.0);
}

TEST(TStack, is_empty_works_correctly)
{
	TStack<double> st;
	EXPECT_EQ(st.isEmpty(), true);
	st.push(1.0);
	EXPECT_EQ(st.isEmpty(), false);
}

TEST(TStack, clear_removes_all_elements)
{
	TStack<double> st;
	st.push(3.0);
	st.push(2.0);
	st.clear();
	EXPECT_EQ(st.isEmpty(), true);
}
