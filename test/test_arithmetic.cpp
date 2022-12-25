#include <gtest.h>
#include <arithmetic.h>



TEST(Arithmetic, throw_wen_zero_division)
{
	ASSERT_ANY_THROW(TPostfix test("1/(2-2)"));
	
}

TEST(Arithmetic, can_create_use_base_operations) { // + - * /
	ASSERT_NO_THROW(TPostfix f("1+2"));
	ASSERT_NO_THROW(TPostfix f("1/2"));
	ASSERT_NO_THROW(TPostfix f("1*2"));
	ASSERT_NO_THROW(TPostfix f("1-2"));
}

TEST(Arithmetic, cant_create_postfix_form_with_one_item) {
	ASSERT_ANY_THROW(TPostfix f("1"));
}

TEST(Arithmetic, can_calculate_correct_postfix) {
	TPostfix f("5.1*(4.2-10)+(2.5+1)/5");
	EXPECT_EQ(f.GetResult(), -28.88);
}

TEST(Arithmetic, cant_calculate_when_error_with_brackets) {
	ASSERT_ANY_THROW(TPostfix f("(a+b"));
}
TEST(Arithmetic, can_create_true_operation) {
	ASSERT_NO_THROW(Operation o("+"));
	ASSERT_NO_THROW(Operation o("-"));
	ASSERT_NO_THROW(Operation o("*"));
	ASSERT_NO_THROW(Operation o("/"));
	ASSERT_NO_THROW(Operation o("("));
	ASSERT_NO_THROW(Operation o(")"));
}

TEST(Arithmetic, can_set_num_value_to_variable) {
	Var x("x");
	ASSERT_NO_THROW(x.SetNum(1));
	EXPECT_EQ(x.GetNum(), 1);
}

TEST(Arithmetic, can_create_lexem_with_double_value) {
	ASSERT_NO_THROW(Num n("3.34"));
}