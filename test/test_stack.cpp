// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> v(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> v(-5));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> v(MaxStackSize + 1));
}

TEST(TStack, cant_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> v(0));
}


TEST(TStack, cant_put_to_FULL_stack)
{
	TStack<int> v(2);
	v.Put(1);
	v.Put(2);
	ASSERT_ANY_THROW(v.Put(4));
}

TEST(TStack, cant_get_of_CLEAR_stack)
{
	TStack<int> v(5);
	ASSERT_ANY_THROW(v.Get());
}



TEST(TStack, can_get_of_stack_about_one)
{
	TStack<int> v(5);
	v.Put(4);
	EXPECT_EQ(4, v.Get());
}

TEST(TStack, can_get_of_stack_about_two)
{
	TStack<int> v(5);
	v.Put(4);
	v.Put(7);
	EXPECT_EQ(7, v.Get());
}

TEST(TStack, can_get_of_stack_about_three)
{
	TStack<int> v(5);
	v.Put(4);
	v.Put(1);
	v.Put(10);
	EXPECT_EQ(10, v.Get());
}


