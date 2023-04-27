#include <ctest.h>
#include <func.h>// for math logic test

CTEST(MATH_LOGIC_TEST_suite, IsCalculatingDistanceTrue)
{
    // When
    const int result_1 = CalculateCenterDistance(10.5, 15, 15, 10);
    const int result_2 = CalculateCenterDistance(100, 50, 10.5, 12);
    const int result_3 = CalculateCenterDistance(0,0,0,0);
    // Then
    const int expected_1 = 6.72681;
    const int expected_2 = 50.0225;
    const int expected_3 = 0;

    ASSERT_DBL_NEAR(expected_1, result_1);
    ASSERT_DBL_NEAR(expected_2, result_2);
    ASSERT_DBL_NEAR(expected_3, result_3);
}