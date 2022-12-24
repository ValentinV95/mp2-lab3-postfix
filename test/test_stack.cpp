// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> stack;
	ASSERT_NO_THROW(TStack<int> stack_copy(stack));
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> stack;
	ASSERT_NO_THROW(stack = stack);
}

TEST(TStack, can_assign_stack_to_another_stack_of_the_same_size)
{
	TStack<double> stack;
	TStack<double> an_stack;
	stack.push(8.5);
	stack.push(4.0);
	an_stack.push(3.3);
	an_stack.push(7.9);
	ASSERT_NO_THROW(an_stack = stack);
}

TEST(TStack, can_assign_stack_to_a_smaller_stack)
{
	TStack<double> stack;
	TStack<double> an_stack;
	stack.push(8.5);
	stack.push(4.0);
	stack.push(5.7);
	an_stack.push(3.3);
	an_stack.push(7.9);
	ASSERT_NO_THROW(an_stack = stack);
}

TEST(TStack, can_assign_stack_to_a_larger_stack)
{
	TStack<double> stack;
	TStack<double> an_stack;
	stack.push(8.5);
	stack.push(4.0);
	an_stack.push(5.7);
	an_stack.push(3.3);
	an_stack.push(7.9);
	ASSERT_NO_THROW(an_stack = stack);
}

TEST(TStack, can_push_an_element_to_the_stack)
{
	TStack<double> stack;
	ASSERT_NO_THROW(stack.push(6.5));
}

TEST(TStack, can_pop_an_element_from_the_stack)
{
	TStack<double> stack;
	stack.push(8.5);
	stack.push(4.0);
	stack.push(5.7);
	ASSERT_NO_THROW(stack.pop());
}

TEST(TStack, cant_pop_an_element_from_an_empty_stack)
{
	TStack<double> stack;
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TStack, can_view_the_top_element_of_the_stack)
{
	TStack<double> stack;
	stack.push(8.5);
	stack.push(4.0);
	stack.push(5.7);
	ASSERT_NO_THROW(stack.top());
}

TEST(TStack, cant_view_the_top_element_on_an_empty_stack)
{
	TStack<double> stack;
	ASSERT_ANY_THROW(stack.top());
}

TEST(TStack, can_check_that_stack_is_empty)
{
	TStack<double> stack;
	EXPECT_EQ(stack.isEmpty(), true);
}

TEST(TStack, can_check_that_stack_is_not_empty)
{
	TStack<double> stack;
	stack.push(0.75);
	EXPECT_EQ(stack.isEmpty(), false);
}

TEST(TStack, can_get_the_stack_size)
{
	TStack<double> stack;
	stack.push(0.75);
	stack.push(6.79);
	stack.push(2.44);
	EXPECT_EQ(stack.size(), 3);
}

TEST(TStack, can_get_zero_stack_size)
{
	TStack<double> stack;
	EXPECT_EQ(stack.size(), 0);
}

TEST(TStack, can_clear_the_stack)
{
	TStack<double> stack;
	stack.push(6.7);
	stack.push(6.8);
	stack.push(6.9);
	ASSERT_NO_THROW(stack.clear());
}