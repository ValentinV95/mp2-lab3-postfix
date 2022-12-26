// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Tstack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Tstack<int> st(3));
}
TEST(Tstack, cant_create_stack_with_negatve_lenght)
{
	ASSERT_ANY_THROW(Tstack<int> st(-1));
}
TEST(Tstack, can_create_copied_stack) 
{
	Tstack<int> st(4);

	st.push(3);
	st.push(2);

	ASSERT_NO_THROW(Tstack<int> st1(st));
}
TEST(Tstack, copied_stack_is_equal_source_one) 
{
	Tstack<int> st(4);
	Tstack<int> st1(4);

	//{3,2,/,-}
	st.push(3);
	st.push(2);
	st1 = st;
	st.clr();
	st.push(3);
	st.push(2);

	EXPECT_EQ(st, st1);
}
TEST(Tstack, coping_change_the_stack_size) 
{
	Tstack<int> st(4);
	Tstack<int> st1(6);

	//{3,2,/,-}
	st.push(3);
	st.push(2);
	st1 = st;

	EXPECT_EQ(4, st1.size());
}
TEST(Tstack, copied_stack_has_own_mem) 
{
	Tstack<int> st(4);
	Tstack<int> st1(4);

	//{3,2,/,-}
	st.push(3);
	st.push(2);
	st1 = st;
	st.clr();
	st.push(3);
	st.push(2);

	EXPECT_NE(&st, &st1);
}
TEST(Tstack, can_insert_elements) 
{
	Tstack<int> st(4);

	ASSERT_NO_THROW(st.push(1));
}
TEST(Tstack, inc_size_when_overflow) 
{
	Tstack<int> st(2);

	//{4,6,1,/}
	st.push(4);
	st.push(6);
	st.push(1);

	EXPECT_EQ(4, st.size());
}
TEST(Tstack, can_extract_element) 
{
	Tstack<int> st(4);

	st.push(2);

	ASSERT_NO_THROW(st.pop());
}
TEST(Tstack, cant_extract_when_empty) 
{
	Tstack<int> st(4);

	ASSERT_ANY_THROW(st.pop());
}
TEST(Tstack, extracted_element_is_equal_to_inserted) 
{
	Tstack<int> st(4);
	
	st.push(2);

	EXPECT_EQ(2, st.pop());
}
TEST(Tstack, can_preview_element) 
{
	Tstack<int> st(4);

	st.push(2);

	ASSERT_NO_THROW(st.peek());
}
TEST(Tstack, cant_preview_empty_stack) 
{
	Tstack<int> st(4);

	ASSERT_ANY_THROW(st.peek());
}
TEST(Tstack, element_in_preview_is_equal_extract) 
{
	Tstack<int> st(4);
	int tmp;

	st.push(2);
	tmp = st.peek();

	EXPECT_EQ(tmp, st.pop());
}
TEST(Tstack, stack_with_zero_elements_is_empty) 
{
	Tstack<int> st(4);

	EXPECT_EQ(true, st.isEmpty());
}
TEST(Tstack, can_get_size) 
{

	Tstack<int> st(4);

	EXPECT_EQ(4, st.size());
}
TEST(Tstack, can_clear_the_stack) 
{
	Tstack<int> st(4);

	st.push(2);

	ASSERT_NO_THROW(st.clr());
}
TEST(Tstack, clear_stack_is_empty) 
{
	Tstack<int> st(4);

	st.push(2);
	st.clr();

	EXPECT_EQ(true, st.isEmpty());
}