// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> a(3));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> a(-5));
}

TEST(Stack, can_create_copied_stack)
{
	Stack<int> a(5);
	a.push(3);

	ASSERT_NO_THROW(Stack<int> b(a));
}

TEST(Stack, copied_stack_is_equal)
{
	Stack<int> a1(3);
	a1.push(3); a1.push(5); a1.push(8);
	Stack<int> a2(a1);
	EXPECT_EQ(8, a2.view_top());
	EXPECT_EQ(3, a2.GetLength());
}

TEST(Stack, can_get_size)
{
	Stack<int> a(2);
	a.push(3); a.push(2);

	EXPECT_EQ(2, a.GetLength());
}

TEST(Stack, correct_check_full_stack)
{
	Stack<int> a(3);
	a.push(2); a.push(6); a.push(5);
	EXPECT_TRUE(a.isFull());
}

TEST(Stack, correct_check_notfull_stack)
{
	Stack<int> a(3);
	a.push(2);
	EXPECT_FALSE(a.isFull());
}

TEST(Stack, correct_check_empty_stack)
{
	Stack<int> a(3);
	EXPECT_TRUE(a.isEmpty());
}

TEST(Stack, correct_check_notempty_stack)
{
	Stack<int> a(3);
	a.push(3);
	EXPECT_FALSE(a.isEmpty());
}

TEST(Stack, can_push_element_when_stack_is_not_full)
{
	Stack<int> a(3);
	a.push(3);
	EXPECT_EQ(3, a.view_top());
}

TEST(Stack, can_push_element_and_give_memory_when_stack_is_full)
{
	Stack<int> a(3);
	a.push(4);
	a.push(5);
	a.push(7);
	a.push(3);
	EXPECT_EQ(3, a.view_top());
	EXPECT_EQ(4, a.GetLength());
}

TEST(Stack, can_pop_element)
{
	Stack<int> a(3);
	a.push(4); a.push(7); a.push(9);
	EXPECT_EQ(9, a.pop());
}

TEST(Stack, cant_pop_element_when_satck_is_empty)
{
	Stack<int> a(3);
	ASSERT_ANY_THROW(a.pop());
}

TEST(Stack, can_view_top_of_stack)
{
	Stack<int> a(3);
	a.push(45); a.push(29); a.push(32);
	EXPECT_EQ(32, a.view_top());
}

TEST(Stack, cant_view_top_of_stack_when_stack_is_empty)
{
	Stack<int> a(3);
	ASSERT_ANY_THROW(a.view_top());
}

TEST(Stack, can_clear_stack)
{
	Stack<int> a(3);
	a.push(46); a.push(23);
	ASSERT_NO_THROW(a.push(92));
	a.Clear();
	ASSERT_ANY_THROW(a.view_top());
}