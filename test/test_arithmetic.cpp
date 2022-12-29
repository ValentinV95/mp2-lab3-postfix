// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Arithmetic_expression, can_create_correct_expression) {
	ASSERT_NO_THROW(Arithmetic_expression expr("x*y"));
}
