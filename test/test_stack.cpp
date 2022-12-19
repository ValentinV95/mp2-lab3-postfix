// тесты для стека

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

TEST(Stack, can_check_if_the_empty_stack_is_empty)
{
	const int size = 3;
	Stack<int> stack(size);
	EXPECT_TRUE(stack.isEmpty());
}

TEST(Stack, can_check_if_the_non_empty_stack_is_empty)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	EXPECT_FALSE(stack.isEmpty());
}

TEST(Stack, can_check_if_the_full_stack_is_full)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	EXPECT_TRUE(stack.isFull());
}

TEST(Stack, can_check_if_the_non_full_stack_is_full)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	EXPECT_FALSE(stack.isFull());
}

TEST(Stack, can_push_element_to_non_full_stack)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	EXPECT_EQ(2, stack.top());
}

TEST(Stack, can_push_element_to_full_stack)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	EXPECT_TRUE(stack.isFull());
	stack.push(4);
	EXPECT_EQ(4, stack.top());
}

TEST(Stack, can_show_top_element)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	EXPECT_EQ(2, stack.top());
}


TEST(Stack, can_pop_element_from_stack)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	stack.pop();
	EXPECT_EQ(1, stack.top());
}


TEST(Stack, can_get_the_number_of_elements_in_the_stack)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	EXPECT_EQ(1, stack.getCount());
}

TEST(Stack, can_clear_the_stack)
{
	const int size = 3;
	Stack<int> stack(size);
	stack.push(1);
	stack.push(2);
	stack.clear();
	EXPECT_TRUE(stack.isEmpty());
}