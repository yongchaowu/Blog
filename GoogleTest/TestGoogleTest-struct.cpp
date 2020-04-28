// TestGoogleTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "gtest/gtest.h"

 bool IsPrime(int n) 
 {
  // Trivial case 1: small numbers
  if (n <= 1) return false;

  // Trivial case 2: even numbers
  if (n % 2 == 0) return n == 2;

  // Now, we have that n is odd and n >= 3.

  // Try to divide n by every odd number i, starting from 3
  for (int i = 3;; i += 2) {
    // We only have to try i up to the squre root of n
    if (i > n / i) break;

    // Now, we have i <= n/i < n.
    // If n is divisible by i, n is not prime.
    if (n % i == 0) return false;
  }

  // n has no integer factor in the range (1, n), and thus is prime.
  return true;
}

 struct T1 {
  int a;
 };
//class FooTest : public ::testing::TestWithParam<int> {

 class FooTest : public ::testing::TestWithParam<struct T1> {
 // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
  //在这里面可以实现fixture类的所有成员
 protected:
      FooTest() {
        // You can do set-up work for each test here.
      }

      ~FooTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
      }

      // If the constructor and destructor are not enough for setting up
      // and cleaning up each test, you can define the following methods:

      void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
      }

      void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
      }

 public:
      struct T1 m_T;
};
//第二步
TEST_P(FooTest, DoesBlah) {
  // Inside a test, access the test parameter with the GetParam() method
  // of the TestWithParam<T> class:
  //在测试中，使用TestWithParam <T>类的GetParam（）方法访问测试参数：
  //int n = GetParam();
  //EXPECT_TRUE(IsPrime
  T1 n = GetParam();
  std::cout << m_T.a<<"----"<< n.a <<std::endl;
  //...
}

//第三步
//第一个参数是前缀；第二个是类名；第三个是参数生成器
//INSTANTIATE_TEST_SUITE_P(MyPrimeParamTest, FooTest,
//                        ::testing::Values(-5, 0, 3, 5, 11));


//std::vector<T1> g_structT;
//INSTANTIATE_TEST_SUITE_P(MyPrimeParamTest, FooTest, ::testing::ValuesIn(g_structT);

INSTANTIATE_TEST_SUITE_P(MyPrimeParamTest, FooTest, ::testing::Values(T1{1}));
//INSTANTIATE_TEST_CASE_P(ttt1, FooTest, ::testing::Values(T1(1));

int main(int argc, char** argv) 
{
  testing::InitGoogleTest(&argc, argv);
  //T1 tmp;
  //tmp.a = 99;
  //g_structT.push_back(tmp);
  return RUN_ALL_TESTS();
}
////---------------------------------------------------------------
//int MyAdd(int a, int b) { return a+b; }
//
//TEST(MyAdd, 4plus4) {
//  EXPECT_EQ(MyAdd(4, 4), 8);
//  EXPECT_TRUE(true);
//}  //通过
//
//TEST(MyAdd, 5plus5) {
//  EXPECT_EQ(MyAdd(5, 5), 8);
//  EXPECT_TRUE(true);
//}  //不通过
//
//int main(int argc, char* argv[]) {
//  testing::InitGoogleTest(&argc, argv);  //将命令行参数传递给gtest
//  return RUN_ALL_TESTS();  // RUN_ALL_TESTS()运行所有测试案例
//  system("pause");
//}
////------------------------------------------------