// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> stak);
}
TEST(Stack, can_create_empty_stack)
{
	Stack<int> stak;
	EXPECT_EQ(stak.IsEmpty(), true);
}
TEST(Stack, empty_check_after_push)
{
	Stack<int> stak;
	stak.Push(4);
	EXPECT_NE(stak.IsEmpty(), true);
}
TEST(Stack, empty_check_after_pop)
{
	Stack<int> stak;
	stak.Push(4);
	stak.Pop();
	EXPECT_EQ(stak.IsEmpty(), true);
}
TEST(Stack, can_push_elem)
{
	Stack<int> stak;
	stak.Push(19);
	EXPECT_EQ(stak.IsEmpty(), false);
}
TEST(Stack, can_pop_elem)
{
	Stack<int> st;
	st.Push(10);
	EXPECT_EQ(st.Pop(), 10);
}
TEST(Stack, push_changes_length_of_stack)
{
	Stack<int> stak;
	EXPECT_EQ(stak.GetSize(), 0);
	stak.Push(1);
	EXPECT_EQ(stak.GetSize(), 1);
}