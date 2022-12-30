// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStack <double> st(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack <double> st(-5));
}

TEST(TStack, throws_when_create_stack_with_zero_length) {
	ASSERT_ANY_THROW(TStack <double> st(0));
}

TEST(TStack, pop_element_from_empty_stack) {
	TStack <double> st(3);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, Top_elem_of_stack_is_correct) {
	TStack <double> st(3);
	st.Push(1);
	EXPECT_EQ(st.TopElem(), 1);
}

TEST(TStack, top_element_from_empty_stack) {
	TStack <double> st(3);
	ASSERT_ANY_THROW(st.TopElem());
}

TEST(TStack, stack_is_full) {
	TStack <double> st(3);
	st.Push(3);
	st.Push(2);
	st.Push(1);
	EXPECT_EQ(st.IsFull(),true);
}

TEST(TStack, clear_works_correctly) {
	TStack <double> st(3);
	st.Push(3);
	st.Push(2);
	st.Push(1);
	st.clear();
	EXPECT_EQ(st.IsEmpty(),true);
}

TEST(TStack, empty_stack) {
	TStack <double> st(3);
	EXPECT_EQ(st.IsEmpty(), true);
}