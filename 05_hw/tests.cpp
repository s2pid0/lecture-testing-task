#include <gtest/gtest.h>
#include "stack.h"

using namespace std;

class StackTest : public testing::Test
{
    void SetUp() override
    {
        stack = new Stack();
    }

    void TearDown() override {
        delete stack;
    }

public:
    Stack* stack;
};

TEST_F(StackTest, initStackTest) {
    Stack f;
    initStack(&f);
    EXPECT_EQ(isEmpty(&f), true);
    delete &f;
}

TEST_F(StackTest, isEmptyTest) {
    EXPECT_EQ(isEmpty(stack), true);
}

TEST_F(StackTest, pushTest) {
    push(stack, 44);
    EXPECT_EQ(getTop(stack)->data, 44);
}

TEST_F(StackTest, popTest) {
    push(stack, 0);
    push(stack, 3);
    push(stack, 11);
    pop(stack);
    EXPECT_EQ(getTop(stack)->data, 3);
}

TEST_F(StackTest, EmptyPopTest) {
    pop(stack);
    EXPECT_EQ(getTop(stack), nullptr);
}


TEST_F(StackTest, destroyStackTests) {
    push(stack, -12);
    push(stack, -31);
    push(stack, 2);
    push(stack, 832);
    
    destroyStack(stack);

    EXPECT_EQ(getTop(stack), nullptr);
}

TEST_F(StackTest, searchByValueTest) {
    push(stack, 12);
    push(stack, -2);
    push(stack, 72);

    EXPECT_EQ(searchByValue(stack, -2)->data, -2);
}

TEST_F(StackTest, searchByIndexTest) {
    push(stack, 12);
    push(stack, 2);
    push(stack, 72);

    EXPECT_EQ(searchByIndex(stack, 2)->data, 12);
}

TEST_F(StackTest, traverseStackTest) {
    testing::internal::CaptureStdout();

    push(stack, 22129);
    push(stack, -12);
    push(stack, 0);
    push(stack, 51242);
    push(stack, -33);

    traverseStack(stack);

    std::string expected = "Stack elements: -33 51242 0 -12 22129 \n";
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}