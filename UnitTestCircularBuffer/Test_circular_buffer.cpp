#include "pch.h"
#include "../CircularBuffer/circular_buffer.h"
#include <iostream>

constexpr std::size_t size{ 4 };
using value_type_tested = int;
using SUT = container::circular_buffer<value_type_tested, size>;

class Test_circular_buffer : public ::testing::Test
{
protected:
	SUT sut{};
};

TEST_F(Test_circular_buffer, internalData)
{
	EXPECT_EQ(0, *(sut.data() + 2));
}

TEST_F(Test_circular_buffer, size)
{
	EXPECT_EQ(4, sut.size());
	sut.push_back(0);
	EXPECT_EQ(4, sut.size());
	sut.push_back(0);
	EXPECT_EQ(4, sut.size());
	sut.push_back(0);
	EXPECT_EQ(4, sut.size());
	sut.push_back(0);
	EXPECT_EQ(4, sut.size());
	sut.push_back(0);
	EXPECT_EQ(4, sut.size());
}
TEST_F(Test_circular_buffer, capacity)
{
	EXPECT_EQ(4, sut.capacity());
}

TEST_F(Test_circular_buffer, front)
{
	*sut.data() = 5;
	EXPECT_EQ(5, sut.front());
}

TEST_F(Test_circular_buffer, back)
{
	*(sut.data() + 3) = 5;
	EXPECT_EQ(5, sut.back());
}

TEST_F(Test_circular_buffer, at)
{
	*(sut.data() + 0) = 11;
	*(sut.data() + 1) = 22;
	*(sut.data() + 2) = 33;
	*(sut.data() + 3) = 44;
	EXPECT_EQ(11, sut.at(0));
	EXPECT_EQ(22, sut.at(1));
	EXPECT_EQ(33, sut.at(2));
	EXPECT_EQ(44, sut.at(3));
}

TEST_F(Test_circular_buffer, invalidIndexShallThrow)
{
	EXPECT_THROW(sut.at(4), std::out_of_range);
}
TEST_F(Test_circular_buffer, push_back)
{
	EXPECT_EQ(0, sut.front());
	EXPECT_EQ(0, sut.back());
	sut.push_back(11);
	EXPECT_EQ(11, sut.front());
	EXPECT_EQ(0, sut.back());
	sut.push_back(22);
	EXPECT_EQ(22, sut.front());
	EXPECT_EQ(0, sut.back());
	sut.push_back(33);
	EXPECT_EQ(33, sut.front());
	EXPECT_EQ(0, sut.back());
	sut.push_back(44);
	EXPECT_EQ(44, sut.front());
	EXPECT_EQ(11, sut.back());
	sut.push_back(55);
	EXPECT_EQ(55, sut.front());
	EXPECT_EQ(22, sut.back());
	sut.push_back(66);
	EXPECT_EQ(66, sut.front());
	EXPECT_EQ(33, sut.back());
	sut.push_back(77);
	EXPECT_EQ(77, sut.front());
	EXPECT_EQ(44, sut.back());
}

TEST_F(Test_circular_buffer, beginIterator)
{
	*sut.data() = 99;
	EXPECT_EQ(99, *sut.begin());
}

TEST_F(Test_circular_buffer, endIterator)
{
	*(sut.data() + 3) = 99;
	EXPECT_EQ(99, *sut.end());
}

TEST_F(Test_circular_buffer, reverseBeginIterator)
{
	*(sut.data() + 3) = 99;
	EXPECT_EQ(99, *sut.rbegin());
}

TEST_F(Test_circular_buffer, reverseEndIterator)
{
	*sut.data() = 99;
	EXPECT_EQ(99, *sut.rend());
}
