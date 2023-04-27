#include <ctest.h>
#include <func.h>// for math logic group of  tests

CTEST(MATH_LOGIC_TEST_suite, IsCalculatingDistanceTrue)
{
    // When
    const float result_1 = round(CalculateCenterDistance(10.5, 15, 15, 10)*10000)/10000;
    const float result_2 = round(CalculateCenterDistance(100, 50, 10.5, 12)*10000)/10000;
    const float result_3 = round(CalculateCenterDistance(0,0,0,0)*10000)/10000;
    // Then
    const float expected_1 = 6.7268;
    const float expected_2 = 50.0225;
    const float expected_3 = 0.f;

    ASSERT_DBL_NEAR(expected_1, result_1);
    ASSERT_DBL_NEAR(expected_2, result_2);
    ASSERT_DBL_NEAR(expected_3, result_3);
}

CTEST(MATH_LOGIC_TEST_suite,IsCalculatingPerimeterTrue)
{   
    // When
    const float result_1 = round(CalculatePerimeter(10)*10000)/10000;
    const float result_2 = round(CalculatePerimeter(15)*10000)/10000;
    const float result_3 = round(CalculatePerimeter(0)*10000)/10000;
    // Then
    const float expected_1 = 62.8319f;
    const float expected_2 = 94.2478f;
    const float expected_3 = 0.f;

    ASSERT_DBL_NEAR(expected_1, result_1);
    ASSERT_DBL_NEAR(expected_2, result_2);
    ASSERT_DBL_NEAR(expected_3, result_3);
}

//CTEST(MATH_LOGIC_TEST_suite,IsCalculatingAreaTrue)
//{

//}