// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(DStack, can_create_stack)
{
    ASSERT_NO_THROW(DStack<int> stack);
}

TEST(Dstack, memory_rellocation_works)
{
    DStack<int> stack;
    ASSERT_NO_THROW(stack.Push(1));
}

TEST(DStack, can_get_stack_size)
{
    DStack<int> stack;
    ASSERT_NO_THROW(stack.size());
}


TEST(DStack, top_of_empty_stack_is_null)
{
    DStack<int> stack;
    EXPECT_EQ(0, stack.size());
}


TEST(DStack, stack_equal_is_right)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    EXPECT_EQ(3, stack.size());
} 


TEST(DStack, cant_return_top_when_stack_is_empty)
{
    DStack<int> stack;
    ASSERT_ANY_THROW(stack.Top());
}


TEST(DStack, can_return_top_when_stack_isnt_empty)
{
    DStack<int> stack;
    stack.Push(1);
    ASSERT_NO_THROW(stack.Top());
}


TEST(DStack, top_is_right)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    EXPECT_EQ(3, stack.Top());
}


TEST(DStack, cant_do_pop_when_stack_is_empty)
{
    DStack<int> stack;
    ASSERT_ANY_THROW(stack.Pop());
}


TEST(DStack, can_do_pop_when_stack_isnt_empty)
{
    DStack<int> stack;
    stack.Push(1);
    ASSERT_NO_THROW(stack.Pop());
}


TEST(DStack, pop_works_correct)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    EXPECT_EQ(3, stack.Pop());
    EXPECT_EQ(2, stack.size());
    EXPECT_EQ(2, stack.Top());
}


TEST(DStack, isnt_empty_when_stack_isnt_empty)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    EXPECT_NE(-1, stack.IsEmpty());
}



TEST(DStack, true_when_stack_is_empty)
{
    DStack<int> stack;
    EXPECT_EQ(true, stack.IsEmpty());
}


TEST(DStack, top_doesnt_change_stack_index)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    stack.Top();
    EXPECT_EQ(3, stack.size());
}


TEST(DStack, can_clean_stack)
{
    DStack<int> stack;
    stack.Push(1); stack.Push(2); stack.Push(3);
    ASSERT_NO_THROW(stack.clear());
    ASSERT_ANY_THROW(stack.Pop());
}

