// тесты для вычисления арифметических выражений
#include "arithmetic.h"
#include <gtest.h>

TEST(TPostfix, can_create_tpostfix_without_infix)
{
    ASSERT_NO_THROW(TPostfix test);
}

TEST(TPostfix, can_create_tpostfix_with_infix)
{
    ASSERT_NO_THROW(TPostfix test("5+5"));
}

TEST(TPostfix, can_set_other_infix)
{
    TPostfix test("5+5");
    ASSERT_NO_THROW(test.setTPostfix("5"));
}

TEST(TPostfix, can_convert_to_lexem_array)
{
    TPostfix test("56.2+576.E89");
    string array[3] = { "56.2", "+", "576.E89" };
    for (size_t i = 0; i < 3; i++)
        EXPECT_EQ(test.getLexem(i), array[i]);
}

TEST(TPostfix, throw_if_opening_bracket_in_wrong_position)
{
    ASSERT_ANY_THROW(TPostfix test("9("));
}

TEST(TPostfix, throw_if_closing_bracket_in_wrong_position)
{
    ASSERT_ANY_THROW(TPostfix test("-)*9"));
}

TEST(TPostfix, throw_if_operation_in_wrong_position)
{
    ASSERT_ANY_THROW(TPostfix test("++9"));
}

TEST(TPostfix, throw_if_minus_in_wrong_position)
{
    ASSERT_ANY_THROW(TPostfix test("(9)-"));
}

TEST(TPostfix, throw_if_name_variables_incorrect)
{
    ASSERT_ANY_THROW(TPostfix test("T"));
    ASSERT_ANY_THROW(TPostfix test("aa"));
}

TEST(TPostfix, throw_if_exponential_notation_is_wrong)
{
    TPostfix test;
    ASSERT_ANY_THROW(test.setTPostfix("9E+6"));
}

TEST(TPostfix, throw_if_number_notation_is_wrong)
{
    TPostfix test;
    ASSERT_ANY_THROW(test.setTPostfix(".6"));
    ASSERT_ANY_THROW(test.setTPostfix("6."));
}

TEST(TPostfix, throw_if_bracket_number_isnt_equal)
{
    TPostfix test;
    ASSERT_ANY_THROW(test.setTPostfix("((9+6)"));
}

TEST(TPostfix, correct_operation_priority)
{
    TPostfix test;
    EXPECT_EQ(test.operation_priority("+"), 1);
    EXPECT_EQ(test.operation_priority("-"), 1);
    EXPECT_EQ(test.operation_priority("*"), 2);
    EXPECT_EQ(test.operation_priority("/"), 2);
    EXPECT_EQ(test.operation_priority("~"), 3);
    EXPECT_EQ(test.operation_priority("("), 0);
}

TEST(TPostfix, correct_converting_string_to_number)
{
    TPostfix test;
    EXPECT_EQ(test.toNumber("96.678"), 96.678);
    EXPECT_EQ(test.toNumber("-96"), -96);
    double temp;
    temp = floor(test.toNumber("-96.45") * pow(10.0, 16)) / pow(10.0, 16);
    EXPECT_EQ(temp, -96.45);
    temp = floor(test.toNumber("-9.456E2") * pow(10.0, 16)) / pow(10.0, 16);
    EXPECT_EQ(temp, -945.6);
}

TEST(TPostfix, correct_converting_to_postfix_form)
{
    string temp = "6989+";
    TPostfix test("69+89");
    test.toPostfix();
    EXPECT_EQ(test.getPostfix(), temp);

    temp = "896978+8989~*-*9+";
    test.setTPostfix("89*(69+78-89*-89)+9");
    test.toPostfix();
    EXPECT_EQ(test.getPostfix(), temp);
}

TEST(TPostfix, correct_calculating)
{
    double temp = 69.0 + 89.0;
    TPostfix test("69+89");
    test.toPostfix();
    test.toCalculate();
    EXPECT_EQ(test.getResult(), temp);

    temp = 89 * (69 + 78 - 89 * (-89)) + 9;
    test.setTPostfix("89*(69+78-89*-89)+9");
    test.toPostfix();
    test.toCalculate();
    EXPECT_EQ(test.getResult(), temp);

    temp = 5 - (-(-(-(4))));
    test.setTPostfix("5----4");
    test.toPostfix();
    test.toCalculate();
    EXPECT_EQ(test.getResult(), temp);
}

TEST(TPostfix, throw_if_division_by_zero)
{
    TPostfix test("8/0");
    test.toPostfix();
    EXPECT_ANY_THROW(test.toCalculate(););
}