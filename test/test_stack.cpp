#include "stack.h"
#include <gtest.h>


TEST(TStack, can_create_stack) {
	ASSERT_NO_THROW(TStack<int> stack(1));
}

TEST(TStack, create_stack_is_empty) {
	TStack<int> stack(1);
	EXPECT_EQ(true, stack.IsEmpty());
}

TEST(TStack, can_push) {
	TStack<int> stack(1);
	ASSERT_NO_THROW(stack.push(1));
}

TEST(TStack, stack_is_not_empty) {
	TStack<int> stack(1);
	stack.push(2);
	EXPECT_EQ(false, stack.IsEmpty());
}


TEST(TStack, can_clean_stack) {
	TStack<int> stack(1);
	stack.push(1);
	stack.clean();
	EXPECT_EQ(stack.IsEmpty(), true);
}
TEST(TStack, can_pop) {
	TStack<int> stack(2);
	stack.push(3);
	EXPECT_EQ(stack.pop(), 3);
}

TEST(TStack, can_check_top_item) {
	TStack<int> stack(1);
	stack.push(10);
	EXPECT_EQ(stack.get_top(), 10);
	EXPECT_EQ(stack.IsEmpty(), false);
}

TEST(TStack, can_monitor_when_stack_is_full) {
	TStack<int> stack(1);
	stack.push(10);
	EXPECT_EQ(stack.IsFull(), true);
}

TEST(TStack, pop_change_size) {
	TStack<int> stack(3);
	int size;
	stack.push(2);
	stack.push(3);
	size = stack.Size();
	stack.pop();
	EXPECT_EQ(stack.Size(), size - 1);
}

TEST(TStack, cant_create_stack_with_negative_size) {
	ASSERT_ANY_THROW(TStack<int> stack(-1));
}

TEST(TStack, cant_pop_item_from_empty_stack) {
	TStack<int> stack(1);
	ASSERT_ANY_THROW(stack.pop());
}

