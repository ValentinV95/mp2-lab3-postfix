// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, return_size_correctly)
{
	TStack<int> a;

	for (size_t i = 0; i < 20; i++)
	{
		EXPECT_EQ(a.size(), i);
		a.push_back(i);
	}
}
TEST(TStack,correct_push_back_and_pop)
{
	TStack<int> a;

	for (size_t i = 1; i < 20; i++)
	{
		a.push_back(i);
	}
	for (size_t i = 19; i >= 1; i--)
	{
		EXPECT_EQ(i, a.pop());
	}
}
TEST(TStack, throw_exception_on_pop_then_no_elems_in_stack)
{
	TStack<int> a;

	ASSERT_ANY_THROW(a.pop());
}
TEST(TStack, return_is_empty_correctly)
{
	TStack<int> a;
	EXPECT_EQ(a.IsEmpty(), 1);

	a.push_back(1);
	EXPECT_EQ(a.IsEmpty(), 0);

	a.pop();
	EXPECT_EQ(a.IsEmpty(), 1);
}
TEST(TStack, show_top_correctly)
{
	TStack<int> a;
	a.push_back(1);
	EXPECT_EQ(a.show(), 1);

	a.push_back(2);
	EXPECT_EQ(a.show(), 2);

	a.pop();
	EXPECT_EQ(a.show(), 1);
}