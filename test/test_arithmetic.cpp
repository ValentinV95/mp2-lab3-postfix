// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


TEST(constant, createconst)
{
	TStack <char> cnt;
	TStack <char> cnt1;
	cnt.push('3');
	cnt.push('.');
	cnt.push('0');
	cnt.push('2');

	cnt1.push('3');
	cnt1.push('.');
	cnt1.push('0');
	cnt1.push('2');

	_Constant cnst(cnt, 1);
	_Constant cnst1(cnt1,  -1);
	
	EXPECT_EQ(cnst.GetValue(), 3.02);
	EXPECT_EQ(cnst1.GetValue(), -3.02);

}

TEST(constant, gettype)
{
	TStack <char> cnt;
	cnt.push('3');
	cnt.push('.');
	cnt.push('0');
	cnt.push('2');
	_Constant cnst(cnt, 1);
	EXPECT_EQ(cnst.GetType(), "constant");
}
TEST(variable, create_variable)
{
	_Variable vb('a',1);
	EXPECT_EQ(vb.GetOperation(), 'a');
}

TEST(variable, get_type)
{
	_Variable vb('a',1);
	EXPECT_EQ(vb.GetType(),"variable");
}

TEST(operation, create_operation)
{
	Operation op('+');
	EXPECT_EQ(op.GetOperation(), '+');
}

TEST(operation, getType)
{
	Operation op('+');
	EXPECT_EQ(op.GetType(), "operation");
}
TEST(operation, getProirity)
{
	Operation op('+');
	Operation op1('*');
	EXPECT_EQ(op.GetPriority(), 1);
	EXPECT_EQ(op1.GetPriority(), 2);
}

TEST(Postfix, correct_input_check)
{
	string s = "()-4";
	string s1 = "-(3+2)";
	string s2 = "+(3+2)";
	string s3 = "/";
	string s4 = "1++1";
	string s5 = "1+2-";
	string s6 = "1^2";
	EXPECT_ANY_THROW(TPostfix a1(s));
	EXPECT_ANY_THROW(TPostfix a2(s1));
	EXPECT_ANY_THROW(TPostfix a3(s2));
	EXPECT_ANY_THROW(TPostfix a4(s3));
	EXPECT_ANY_THROW(TPostfix a5(s4));
	EXPECT_ANY_THROW(TPostfix a6(s5));
	EXPECT_ANY_THROW(TPostfix a7(s6));
}

TEST(Postfix, postfixformcheck)
{
	string s = "2*(-3.8-3+10)*a";
	TPostfix tst1(s);

	EXPECT_EQ(tst1._GetPostfix() ,"2-3.83-10+*a*");
}

TEST(Postfix, calculate)
{
	string s = "2*(-3.8-3+10)*2";
	TPostfix tst1(s);

	EXPECT_EQ(tst1.Calculate(), 12.8);
}