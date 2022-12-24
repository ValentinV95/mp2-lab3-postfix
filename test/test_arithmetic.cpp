// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>


TEST(Infix_form, empty_string)
{
	string a;
	a.clear();
	

	EXPECT_ANY_THROW(TPostfix p(a, false,1););
}

TEST(Infix_form, infix_witout_spaces)
{
	string a = "1.2  3  4  +     7 -      x";
	a=without_spaces(a);
	EXPECT_EQ(a, "1.234+7-x");
}

TEST(Infix_form, arithmetic_check)
{
	string a1 = "()+1";
	string a2 = "-(1+3)";
	string a3 = "*2+3";
	string a4 = "-1-+2";
	string a5 = "2//1";
	string a6 = "-2+3-";
	string a7 = "()";
	string a8 = "-(2)";


	string a13 = "1+(2*3)-4)+2";
	string a14 = "-1+7-&6";
//	string a15 = "2/0";

	EXPECT_ANY_THROW(TPostfix b1(a1,0,1););
	EXPECT_ANY_THROW(TPostfix b2(a2,0, 1););
	EXPECT_ANY_THROW(TPostfix b3(a3, 0, 1););
	EXPECT_ANY_THROW(TPostfix b4(a4, 0, 1););
	EXPECT_ANY_THROW(TPostfix b5(a5, 0, 1););
	EXPECT_ANY_THROW(TPostfix b6(a6, 0, 1););
	EXPECT_ANY_THROW(TPostfix b7(a7, 0, 1););
	EXPECT_ANY_THROW(TPostfix b8(a8, 0, 1););

	EXPECT_ANY_THROW(TPostfix b13(a13, 0, 1););
	EXPECT_ANY_THROW(TPostfix b14(a14, 0, 1););

	//TPostfix b15(a15, 0, 1);
	//b15.to_postfix_form(0,1);
	//EXPECT_ANY_THROW(b15.calculation(1));

}


TEST(class_Const, get_double)
{
	Tstack<char> a;
	Tstack<char> b;

	a.Push('2');
	a.Push('1');

	b.Push('5');
	b.Push('.');
	b.Push('3');

	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Const(a, a, -1, 0);
	l[1] = new Const(b, b, 1, 0);

	int ans1 = 0;
	int ans2 = 0;


	if (abs(l[0]->get_double() + 21) <0.00000000000001 ) ans1++;
	if ((l[1]->get_double() - 5.3) < 0.00000000000001) ans2++;


	EXPECT_EQ(ans1, 1);
	EXPECT_EQ(ans2, 1);
}



TEST(class_Const, get_minus)
{
	Tstack<char> a;
	Tstack<char> b;

	a.Push('2');
	a.Push('1');

	b.Push('5');
	b.Push('.');
	b.Push('3');

	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Const(a, a, -1, 0);
	l[1] = new Const(b, b, -1, 0);

	int ans1 = 0;
	int ans2 = 0;

	if (l[0]->get_double() < 0) ans1++;
	if (l[1]->get_double() < 0) ans2++;

	EXPECT_EQ(ans1, 1);
	EXPECT_EQ(ans2, 1);
}

TEST(class_Const, is_operand_only)
{
	Tstack<char> b;

	b.Push('5');
	b.Push('.');
	b.Push('3');

	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Const();
	l[1] = new Const(b, b, -1, 0);

	EXPECT_EQ(l[0]->isOperand(), 1);
	EXPECT_EQ(l[0]->isOperation(), 0);
	EXPECT_EQ(l[1]->isOperand(), 1);
	EXPECT_EQ(l[1]->isOperation(), 0);
}

TEST(class_Const, is_constanta_type)
{
	Tstack<char> b;

	b.Push('5');
	b.Push('.');
	b.Push('3');

	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Const();
	l[1] = new Const(b, b, -1, 0);

	EXPECT_EQ(l[0]->get_type(), 1);
	EXPECT_EQ(l[1]->get_type(), 1);
}







TEST(class_Var, get_minus)
{

	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Var( 'x', -1, 0);
	l[1] = new Var( 'y', 1, 0);

	int ans1 = 0;
	int ans2 = 0;

	if (l[0]->get_double() < 0) ans1++;
	if (l[1]->get_double() > 0) ans2++;

	EXPECT_EQ(ans1, 1);
	EXPECT_EQ(ans2, 1);
}

TEST(class_Var, is_operand_only)
{
	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Var('x', 1, 0);
	l[1] = new Var();


	EXPECT_EQ(l[0]->isOperand(), 1);
	EXPECT_EQ(l[0]->isOperation(), 0);
	EXPECT_EQ(l[1]->isOperand(), 1);
	EXPECT_EQ(l[1]->isOperation(), 0);


}

TEST(class_Var, is_variable_type)
{
	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Var('x', 1, 0);
	l[1] = new Var();

	EXPECT_EQ(l[0]->get_type(), 2);
	EXPECT_EQ(l[1]->get_type(), 2);
}



TEST(class_Operation, is_operation_only)
{
	LEXEM** l;
	l = new LEXEM * [2];

	l[0] = new Operation();
	l[1] = new Operation('+');

	EXPECT_EQ(l[0]->isOperand(), 0);
	EXPECT_EQ(l[0]->isOperation(), 1);
	EXPECT_EQ(l[1]->isOperand(), 0);
	EXPECT_EQ(l[1]->isOperation(), 1);

	
}

TEST(class_Operation, get_operation_char)
{
	LEXEM** l;
	l = new LEXEM * [6];

	l[0] = new Operation('-');
	l[1] = new Operation('+');
	l[2] = new Operation('*');
	l[3] = new Operation('/');
	l[4] = new Operation('(');       // Yes. I put them in Operation class  (O_O )
	l[5] = new Operation(')');

	EXPECT_EQ(l[0]->get_char_op(), '-');
	EXPECT_EQ(l[1]->get_char_op(), '+');
	EXPECT_EQ(l[2]->get_char_op(), '*');
	EXPECT_EQ(l[3]->get_char_op(), '/');
	EXPECT_EQ(l[4]->get_char_op(), '(');
	EXPECT_EQ(l[5]->get_char_op(), ')');
}

TEST(class_Operation, correct_priority_set)
{
	LEXEM** l;
	l = new LEXEM * [6];

	l[0] = new Operation('-');
	l[1] = new Operation('+');
	l[2] = new Operation('*');
	l[3] = new Operation('/');
	l[4] = new Operation('(');      
	l[5] = new Operation(')');


	EXPECT_EQ(l[0]->get_priority(), 1);
	EXPECT_EQ(l[1]->get_priority(), 1);
	EXPECT_EQ(l[2]->get_priority(), 2);
	EXPECT_EQ(l[3]->get_priority(), 2);

	EXPECT_EQ(l[4]->get_priority(), 10);  // just in case
	EXPECT_EQ(l[5]->get_priority(), 10);

}

TEST(class_Operation, correct_type_set)
{
	LEXEM** l;
	l = new LEXEM * [6];

	l[0] = new Operation('-');
	l[1] = new Operation('+');
	l[2] = new Operation('*');
	l[3] = new Operation('/');
	l[4] = new Operation('(');
	l[5] = new Operation(')');

	EXPECT_EQ(l[0]->get_type(), 3);
	EXPECT_EQ(l[1]->get_type(), 3);
	EXPECT_EQ(l[2]->get_type(), 3);
	EXPECT_EQ(l[3]->get_type(), 3);
	EXPECT_EQ(l[4]->get_type(), -1);
	EXPECT_EQ(l[5]->get_type(), -2);


}






TEST(class_TPostfix, infix_correct_size)
{
	string a1 = "1+3";
	string a2 = "1--4";
	string a3 = "1+(2+(3-1))";

	TPostfix b1(a1, 1, 1);
	TPostfix b2(a2, 1, 1);
	TPostfix b3(a3, 1, 1);

	EXPECT_EQ(b1.get_infix_len(), 3);
	EXPECT_EQ(b2.get_infix_len(), 4);
	EXPECT_EQ(b3.get_infix_len(), 11);
}

TEST(class_TPostfix, lexem_correct_size)
{
	string a1 = "1+3";
	string a2 = "1--4";
	string a3 = "1+(2+(3-1))";

	TPostfix b1(a1, 1, 1);
	TPostfix b2(a2, 1, 1);
	TPostfix b3(a3, 1, 1);

	EXPECT_EQ(b1.get_true_size(), 3);
	EXPECT_EQ(b2.get_true_size()+1, 4);
	EXPECT_EQ(b3.get_true_size(), 7);
}


TEST(class_TPostfix, parentheses_correct_size)
{
	string a1 = "1+3";
	string a2 = "1-(-4)";
	string a3 = "1+(2+(3-1))";

	TPostfix b1(a1, 1, 1);
	TPostfix b2(a2, 1, 1);
	TPostfix b3(a3, 1, 1);

	EXPECT_EQ(b1.get_c_k1(), 0);
	EXPECT_EQ(b2.get_c_k1(), 1);
	EXPECT_EQ(b3.get_c_k1(), 2);

	EXPECT_EQ(b1.get_c_k2(), 0);
	EXPECT_EQ(b2.get_c_k2(), 1);
	EXPECT_EQ(b3.get_c_k2(), 2);

}











TEST(class_TPostfix, Postfix_work)
{
	string a1 = "1+-13+(-1+13)"; //  0
	string a2 = "-1*-2*-3*-4/-3/-4/-2+1";//  0
	string a3 = "1/10/10";//  1/100
	string a4 = "4/2*2"; //  4
	string a5 = "2/(1--1)";//  1


	TPostfix b1(a1, 0, 1);
	TPostfix b2(a2, 0, 1);
	TPostfix b3(a3, 0, 1);
	TPostfix b4(a4, 0, 1);
	TPostfix b5(a5, 0, 1);


	b1.to_postfix_form(0, 1);
	b2.to_postfix_form(0, 1);
	b3.to_postfix_form(0, 1);
	b4.to_postfix_form(0, 1);
	b5.to_postfix_form(0, 1);

	int ans1 = 0;
	int ans2 = 0;
	int ans3 = 0;
	int ans4 = 0;
	int ans5 = 0;

	if (abs(b1.calculation(1) - 0) < 0.00000000000001) ans1++;
	if (abs(b2.calculation(1) - 0) < 0.00000000000001) ans2++;
	if (abs(b3.calculation(1) - 0.01) < 0.00000000000001) ans3++;
	if (abs(b4.calculation(1) - 4) < 0.00000000000001) ans4++;
	if (abs(b5.calculation(1) - 1) < 0.00000000000001) ans5++;

	EXPECT_EQ(ans1, 1);
	EXPECT_EQ(ans2, 1);
	EXPECT_EQ(ans3, 1);
	EXPECT_EQ(ans4, 1);
	EXPECT_EQ(ans5, 1);

}


















TEST(functions, get_priority_outside_work_properly)
{
	EXPECT_EQ(get_priority_outside('-'), 1);
	EXPECT_EQ(get_priority_outside('+'), 1);
	EXPECT_EQ(get_priority_outside('*'), 2);
	EXPECT_EQ(get_priority_outside('/'), 2);
}

