// тесты для стека

#include "stack.h"
#include <gtest.h>


TEST(Stack,can_be_created_with_different_types)
{
	Tstack<int> a1;
	Tstack<unsigned int> a2;
	Tstack<float> a3;
	Tstack<double> a4;
	Tstack<char> a5;

	a1.Push(1);
	a2.Push(2);
	a3.Push(3.1);
	a4.Push(4.2);
	a5.Push('5');

	int k3=0;
	int k4 = 0;
	if ((a3.Pop() - 3.1) < 0.000000000000001)
	{
		k3++;
	}
	if ((a4.Pop() - 4.2) < 0.000000000000001)
	{
		k4++;
	}

	EXPECT_EQ(a1.Pop() , 1);
	EXPECT_EQ(a2.Pop() , 2);
	EXPECT_EQ(k3 , 1);
	EXPECT_EQ(k4 , 1);
	EXPECT_EQ(a5.Pop() , '5');
}

TEST(Stack, can_be_created_with_template_types)
{
	class TMP
	{
	public:
		int data=0;
		TMP()
		{
			data = 12;
		}

		int get_data() { return data; }
	};


	TMP t;

	Tstack<TMP> a;

	a.Push(t);

	EXPECT_EQ(a.Pop().get_data() , 12);

}

TEST(Stack,correct_Push_and_Pop)
{
	Tstack<int> a;
	a.Push(12);
	a.Push(13);
	a.Push(22);
	a.Push(1);
	a.Push(47);
	a.Push(99);

	EXPECT_EQ(a.Pop(),99 );
	EXPECT_EQ(a.Pop(),47 );
	EXPECT_EQ(a.Pop(), 1);
	EXPECT_EQ(a.Pop(),22 );
	EXPECT_EQ(a.Pop(), 13);
	EXPECT_EQ(a.Pop(),12 );
}

TEST(Stack, correct_check_of_Full_and_Empty)
{
	Tstack<int> a;
	EXPECT_EQ(a.isEmpty(), 1);
	EXPECT_EQ(a.isFull(), 0);

	a.Push(12);
	EXPECT_EQ(a.isEmpty(), 0);
	EXPECT_EQ(a.isFull(), 1);
}

TEST(Stack, correct_size)
{
	Tstack<int> a;
	Tstack<int> b;
	Tstack<int> c;

	a.Push(10);
	a.Push(10);
	a.Push(10);
	a.Push(10);
	a.Push(10);
	a.Push(10);

	b.Push(10);
	b.Push(10);

	EXPECT_EQ(a.size(), 6);
	EXPECT_EQ(b.size(), 2);
	EXPECT_EQ(c.size(), 0);
}

TEST(Stack, create_with_already_existed_memory_size)
{
	Tstack<int> a(4);
	a.Push(1);
	a.Push(1);

	EXPECT_EQ(a.size(), 2);
	EXPECT_EQ(a.isFull(), 0);
	EXPECT_EQ(a.isEmpty(), 0);
}
