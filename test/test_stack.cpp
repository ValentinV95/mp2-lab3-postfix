// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
    ASSERT_NO_THROW(Stack<int> stack);
}

TEST(Stack, can_create_copied_stack)
{
    Stack<int> stack1;
    for (int i = 0; i < stack1.size(); i++)
        stack1.push(i);
    ASSERT_NO_THROW(Stack<int> stack2(stack1));
    Stack<int> stack2(stack1);
    for (int i = 0; i < stack2.size(); i++)
        EXPECT_EQ(stack1.pop(), stack2.pop());
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
    Stack<int> stack1;
    for (int i = 0; i < stack1.size(); i++)
        stack1.push(i);
    Stack<int> stack2(stack1);
    for (int i = 0; i < stack2.size(); i++)
        EXPECT_EQ(stack1.pop(), stack2.pop());
}

TEST(Stack, copied_stack_has_its_own_memory)
{
    Stack<int> stack1;
    Stack<int> stack2(stack1);
    for (int i = 0; i < stack1.size(); i++)
        stack2.push(i);
    for (int i = 0; i < stack1.size(); i++)
        EXPECT_NE(stack1.pop(), stack2.pop());
}

TEST(Stack, can_get_stack_element_number)
{
    Stack<int> stack;
    ASSERT_NO_THROW(stack.size());
    EXPECT_EQ(0, stack.size());
}

TEST(Stack, true_when_stack_is_empty)
{
    Stack<int> stack;
    EXPECT_EQ(true, stack.isEmpty());
}

TEST(Stack, false_when_stack_isnt_empty)
{
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(false, stack.isEmpty());
}

TEST(Stack, can_set_and_get_element)
{
    Stack<int> stack;
    ASSERT_NO_THROW(stack.push(4));
    stack.push(4);
    ASSERT_NO_THROW(stack.pop());
    EXPECT_EQ(4, stack.pop());
}

TEST(Stack, throws_when_get_element_in_empty_stack)
{
    Stack<int> stack;
    ASSERT_ANY_THROW(stack.pop());
}

TEST(Stack, other_index_after_push)
{
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(0, stack.size() - 1);
}

TEST(Stack, more_memory_after_push)
{
    Stack<int> stack;
    for (int i = 0; i < 5; i++)
        stack.push(i);
    ASSERT_NO_THROW(stack.push(1));
}

TEST(Stack, get_top_element)
{
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(1, stack.top());
}

TEST(Stack, method_top_dont_change_stack_index)
{
    Stack<int> stack;
    stack.push(1);
    stack.top();
    EXPECT_EQ(0, stack.size() - 1);
}

TEST(Stack, throws_when_get_top_element_in_empty_stack)
{
    Stack<int> stack;
    ASSERT_ANY_THROW(stack.top());
}

TEST(Stack, can_clean_stack)
{
    Stack<int> stack;
    stack.push(1);
    ASSERT_NO_THROW(stack.clear());
    ASSERT_ANY_THROW(stack.pop());
}