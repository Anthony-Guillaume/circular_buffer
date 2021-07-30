#include "pch.h"
#include "../CircularBuffer/circular_iterator.h"

constexpr std::size_t capacity{ 4 };
using value_type_tested = int;
using SUT = circular_iterator<value_type_tested, capacity>;

class ClassType 
{
public: 
	ClassType(int a) : a{ a } {}
	int a{ 0 }; 
};


class Test_circular_iterator : public ::testing::Test
{
protected:
	value_type_tested buffer[4]{ 11, 22, 33, 44 };
};

class Test_access : public Test_circular_iterator
{
};
TEST_F(Test_access, offsetLesserThanCapacity)
{
	constexpr auto offset{ 2 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[offset]);
	EXPECT_EQ(*sut, sut[offset]);
}

TEST_F(Test_access, offsetGreaterThanCapacity)
{
	constexpr auto offset{ 9 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[1]);
	EXPECT_EQ(*sut, sut[1]);
}

TEST_F(Test_access, offsetGreaterThanCapacityA)
{
	constexpr auto offset{ 9 };
	ClassType buffer[4]{ ClassType{11}, ClassType{22}, ClassType{33}, ClassType{44} };
	circular_iterator<ClassType, capacity> sut{ buffer, offset };
	EXPECT_EQ(sut->a, buffer[1].a);
}

class Test_operator : public Test_circular_iterator
{
};

TEST_F(Test_operator, postIncrement)
{
	constexpr auto offset{ 1 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[1]);
	sut++;
	EXPECT_EQ(*sut, buffer[2]);
	sut++;
	EXPECT_EQ(*sut, buffer[3]);
	sut++;
	EXPECT_EQ(*sut, buffer[0]);
	sut++;
	EXPECT_EQ(*sut, buffer[1]);
}

TEST_F(Test_operator, preIncrement)
{
	constexpr auto offset{ 1 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[1]);
	++sut;
	EXPECT_EQ(*sut, buffer[2]);
	++sut;
	EXPECT_EQ(*sut, buffer[3]);
	++sut;
	EXPECT_EQ(*sut, buffer[0]);
	++sut;
	EXPECT_EQ(*sut, buffer[1]);
}

TEST_F(Test_operator, postDecrement)
{
	constexpr auto offset{ 1 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[1]);
	sut--;
	EXPECT_EQ(*sut, buffer[0]);
	sut--;
	EXPECT_EQ(*sut, buffer[3]);
	sut--;
	EXPECT_EQ(*sut, buffer[2]);
	sut--;
	EXPECT_EQ(*sut, buffer[1]);
}

TEST_F(Test_operator, preDecrement)
{
	constexpr auto offset{ 1 };
	SUT sut{ buffer, offset };
	EXPECT_EQ(*sut, buffer[1]);
	--sut;
	EXPECT_EQ(*sut, buffer[0]);
	--sut;
	EXPECT_EQ(*sut, buffer[3]);
	--sut;
	EXPECT_EQ(*sut, buffer[2]);
	--sut;
	EXPECT_EQ(*sut, buffer[1]);
}

TEST_F(Test_operator, diff)
{
	constexpr auto offset{ 0 };
	SUT sut1{ buffer, offset };
	SUT sut2{ sut1 + 2 };
	EXPECT_EQ(sut1, sut2 - 2);
}

TEST_F(Test_operator, additionAssignment)
{
	constexpr auto offset{ 0 };
	SUT sut{ buffer, offset };
	sut += 2;
	EXPECT_EQ(*sut, buffer[2]);
}

TEST_F(Test_operator, subtractionAssignment)
{
	constexpr auto offset{ 0 };
	SUT sut{ buffer, offset };
	sut -= 1;
	EXPECT_EQ(*sut, buffer[3]);
}

TEST_F(Test_operator, comparison)
{
	SUT sut1{ buffer, 0 };
	SUT sut2{ buffer, 2 };
	SUT sut3{ buffer, 9 };
	SUT sut4{ buffer, 25 };
	EXPECT_LT(sut1, sut2);
	EXPECT_LT(sut2, sut3);
	EXPECT_LT(sut3, sut4);
}