#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "../main.cpp"

//include mock
#include "mock/MockCalculator.h"


class MainTestFixture : public ::testing::Test {
public:
    void SetUp() override  {
        mockCalculator = new MockCalculator();
        main = new Main();
    }

    void TearDown() override  {
        delete mockCalculator;
        delete main;
    }

    Main* main;
  };

TEST_F(MainTestFixture, TestCase_Add) {

    EXPECT_CALL(*mockCalculator, add(::testing::_, ::testing::_))
        .WillRepeatedly(::testing::Return(6));
    int result = main->increase(10);
    ASSERT_EQ(result, 6);
}


// int add(int a, int b)
// {
//     return a + b;
// }

// TEST(TestSuite1, TestCase1)
// {
//     ASSERT_EQ(3, add(1, 2));
// }

