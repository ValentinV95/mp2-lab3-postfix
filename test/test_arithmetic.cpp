// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(class_Operand, can_make_operand)
{
	ASSERT_NO_THROW(Operand("23432"));
}

TEST(class_Operand, can_whatis_for_operand)
{
	Lexems* a[2];
	a[0] = new Operand("34,54");
	EXPECT_EQ("Operand", a[0]->whatis());
}

TEST(class_Operand, can_todo_for_operand)
{
	Stack<double> S(2);
	Lexems* a[2];
	a[0] = new Operand("34,54");
	a[0]->ToDo(S);
	EXPECT_EQ(34.54, S.view_top());
}

TEST(class_Operator, can_make_operator)
{
	ASSERT_NO_THROW(Operator('*'));
}

TEST(class_Operator, can_whatis_for_operator)
{
	Lexems* a[2];
	a[0] = new Operator('*');
	EXPECT_EQ("Operator", a[0]->whatis());
}

TEST(class_Operator, can_todo_for_operator)
{
	Stack<double> S(2);
	S.push(3); S.push(5);
	Lexems* a[2];
	a[0] = new Operator('*');
	a[0]->ToDo(S);
	EXPECT_EQ(15, S.view_top());
}

TEST(class_Operator, throw_when_divisionbyzero_in_todo_for_operator)
{
	Stack<double> S(2);
	S.push(3); S.push(0);
	Lexems* a[2];
	a[0] = new Operator('/');
	ASSERT_ANY_THROW(a[0]->ToDo(S););
}

TEST(class_Operator, can_prioritet)
{
	Lexems* a[5];
	a[0] = new Operator('~'); a[3] = new Operator('+');
	a[1] = new Operator('*'); a[4] = new Operator('-');
	a[2] = new Operator('/');
	EXPECT_EQ(1, a[0]->prioritet());
	EXPECT_EQ(2, a[1]->prioritet());
	EXPECT_EQ(2, a[2]->prioritet());
	EXPECT_EQ(3, a[3]->prioritet());
	EXPECT_EQ(3, a[4]->prioritet());
}

TEST(class_Operator, throw_when_unidentified_operations)
{
	ASSERT_ANY_THROW(Operator('&'));
}

TEST(class_Var, can_make_var)
{
	ASSERT_NO_THROW(Var('x'));
}

TEST(class_Var, can_whatis_for_var)
{
	Lexems* a[2];
	a[0] = new Var('x');
	EXPECT_EQ("Var", a[0]->whatis());
}

/*TEST(calss_Var, can_todo_for_var)  //user enter number in console
{
	Stack<double> S(2);
	Lexems* a[2];
	a[0] = new Var('x');
	a[0]->ToDo(S);
	EXPECT_EQ(15, S.view_top());
}*/

TEST(Postfix, correct_posfix_constract)
{
	ASSERT_NO_THROW(TPostfix("(a+12*23,45/d-0,23e-1)*(f+45,678*h)"));
}

//check correct postfix and infix

TEST(Postfix, throw_when_no_correct_use_bracket_end)
{
	ASSERT_ANY_THROW(TPostfix("(4+5-3))"));
}

TEST(Postfix, throw_when_no_correct_use_bracket_start)
{
	ASSERT_ANY_THROW(TPostfix("(4+(5-3)"));
}

TEST(Postfix, throw_when_no_correct_var)
{
	ASSERT_ANY_THROW(TPostfix("(4+(x1-3)"));
}

TEST(Postfix, throw_when_no_correct_operand)
{
	ASSERT_ANY_THROW(TPostfix("(4+(14y-3)"));
}

TEST(Postfix, throw_when_no_correct_binary_operator_minus)
{
	ASSERT_ANY_THROW(TPostfix("(4+14-3-)"));
}

TEST(Postfix, throw_when_no_correct_binary_operator_plus)
{
	ASSERT_ANY_THROW(TPostfix("(+4+14-3)"));
}

TEST(Postfix, throw_when_no_correct_binary_operator_multiply)
{
	ASSERT_ANY_THROW(TPostfix("*(4+14-3-)"));
}

TEST(Postfix, throw_when_no_correct_binary_operator_div)
{
	ASSERT_ANY_THROW(TPostfix("4+14-3-/"));
}

TEST(Global_function, correct_integer_convert)
{
	std::string example("345");
	EXPECT_EQ(345, convert(example));
}

TEST(Global_function, correct_double_convert)
{
	std::string example("345,564");
	EXPECT_EQ(345.564, convert(example));
}

TEST(Global_function, correct_double_in_standart_view_convert)
{
	std::string example("5,56e-1");
	EXPECT_EQ(0.556, round(convert(example) * 100000)/100000);
}

TEST(Global_function, correct_less_1_convert)
{
	std::string example(",56e-1");
	EXPECT_EQ(0.056, round(convert(example) * 100000) / 100000);
}

TEST(Global_function, throw_when_no_correct_number_with_e)
{
	ASSERT_ANY_THROW(convert("3e,42e-20"));
}

TEST(Global_function, throw_when_no_correct_number_with_point)
{
	ASSERT_ANY_THROW(convert("3,42e-2,0"));
}

TEST(Global_function, is_operand)
{
	EXPECT_TRUE(isOperand('4'));
}

TEST(Global_function, is_not_operand)
{
	EXPECT_FALSE(isOperand('-'));
}

TEST(Global_function, is_operator)
{
	EXPECT_TRUE(isOperator('/'));
}

TEST(Global_function, is_not_operator)
{
	EXPECT_FALSE(isOperator('n'));
}

TEST(Global_function, is_var)
{
	EXPECT_TRUE(isVar('x'));
}

TEST(Global_function, is_not_var)
{
	EXPECT_FALSE(isVar('9'));
}
