// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_created_with_different_type)
{
	TStack<double> _double;
	TStack<char> _char;
	TStack<int> _int;
	_double.push(1.02);
	_double.push(1.26);
	_char.push('a');
	_char.push('b');
	_int.push(3);
	_int.push(8);

	EXPECT_EQ(_double.pop(), 1.26);
	EXPECT_EQ(_char.pop(), 'b');
	EXPECT_EQ(_int.pop(), 8);
}

TEST(Stack, correct_push_pop_top)
{
	TStack<int> _int;
	_int.push(2);
	_int.push(6);
	EXPECT_EQ(_int.pop(), 6);
	EXPECT_EQ(_int.top(), 2);
}

TEST(Stack, correct_empty_size)
{
	TStack <int> _int;
	TStack<int> _int2;
	_int.push(3);
	_int.push(4);
	EXPECT_EQ(_int.size(), 2);
	EXPECT_EQ(_int2.empty(), 1);
}

TEST(Stack, can_create_stack_class)
{
	class T {
	private:
		int a;
	public:
		T()
		{
			a = 0;
		}
		T(int b)
		{
			a = b;
		}
		int Ret()
		{
			return a;
		}
	};

	T tmp(7);
	T tmp2(8);

	TStack<T> stck;
	stck.push(tmp);
	stck.push(tmp2);
	EXPECT_EQ(stck.size(), 2);
	EXPECT_EQ(stck.pop().Ret(), 8);
	EXPECT_EQ(stck.top().Ret(), 7);
	EXPECT_EQ(stck.pop().Ret(), 7);
	EXPECT_EQ(stck.empty(), 1);


}