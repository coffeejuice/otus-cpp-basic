#include <gtest/gtest.h>

#include <iostream>

//function to test
bool is_even(int a)
{
    return a % 2 == 0;
}

//fixture must be inhereted from testing::TestWithParam
class ParamsExampleTest : public testing::TestWithParam<int>
{
};

TEST_P(ParamsExampleTest, IsEven) {
    std::cout << "test case for param = "<< GetParam() << std::endl;
    ASSERT_TRUE(is_even(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(EvenNumbers,
                         ParamsExampleTest,
                         testing::Values(2, 4, 6, 1082, 11));


TEST(NonParamsTest, IsEven) {
    int arr[] = {2, 4, 6, 79, 10};
    int arrSize = sizeof(arr)/sizeof(int);

    for (int i = 0; i < arrSize; ++i)
        ASSERT_TRUE(is_even(arr[i])); //can't understand where is failure
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
