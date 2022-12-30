// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_tpostfix_with_infix)
{
    string str = "x+y";
    ASSERT_NO_THROW(TPostfix tmp(str));
}


TEST(TPostfix, error_when_unequal_quantity_of_brackets_end)
{
    string str = "(x+y))";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, error_when_unequal_quantity_of_brackets_begin)
{
    string str = "((x+y)";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, error_when_unequal_quantity_of_brackets_middle)
{
    string str = "((x+y+((x-z))";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, error_when_open_brackets_in_wrong_position)
{
    string str = "x+(y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, error_when_close_brackets_in_wrong_position)
{
    string str = "x+)y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, throw_if_operation_in_wrong_position)
{
    string str = "x++y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, throw_if_operand_in_wrong_position)
{
    string str = "xy+1";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, throw_if_point_in_wrong_position)
{
    string str = "x+.y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, throw_if_e_in_wrong_position)
{
    string str = "x+ey";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, throw_if_digit_in_wrong_position)
{
    string str = "x+1y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}



TEST(TPostfix, throw_if_first_lexem_is_wrong)
{
    string str = ")x+y";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}



TEST(TPostfix, throw_if_last_lexem_is_wrong)
{
    string str = "x+y+";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}


TEST(TPostfix, correct_convertation_string_to_number)
{
    string str = "10794";
    TPostfix tmp(str);
    EXPECT_EQ(10794, tmp.toNumber("10794"));
}

TEST(TPostfix, correct_convertation_string_with_dot_to_number)
{
    string str = "107.3";
    TPostfix tmp(str);
    EXPECT_EQ(107.3, tmp.toNumber("107.3"));
}

TEST(TPostfix, correct_convertation_string_with_dot_and_e_to_number)
{
    string str = "107.3e2";
    TPostfix tmp(str);
    EXPECT_EQ(10730, tmp.toNumber("107.3e2"));
}


TEST(TPostfix, correct_get_operands)
{
    string str = "x+y";
    TPostfix tmp(str);
    EXPECT_EQ("xy", tmp.GetOperands());
}


TEST(TPostfix, correct_get_infix)
{
    string str = "x+y";
    TPostfix tmp(str);
    EXPECT_EQ(str, tmp.GetInfix());
}


TEST(TPostfix, correct_get_postfix)
{
    string str = "x+y-(3+2.2e1)";
    TPostfix tmp(str);
    EXPECT_EQ("xy+32.2e1+-", tmp.GetPostfix());
}


TEST(TPostfix, correct_calculation)
{
    string str = "x+y-(3+2.2e1)";
    TPostfix tmp(str);
    map<char, double> values;
    values = { {'x',10}, {'y', 2} };
    EXPECT_EQ(-13, tmp.Calculate(values));
}


