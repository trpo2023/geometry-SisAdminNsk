#include <ctest.h>
#include <func.h> //for math logic group of  tests

CTEST(MATH_LOGIC_TEST_suite, IsCalculatingDistanceTrue)// Calculate distance
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

CTEST(MATH_LOGIC_TEST_suite,IsCalculatingPerimeterTrue)// Calculate Perimeter
{   
    // When
    const float result_1 = round(CalculatePerimeter_test(10)*10000)/10000;
    const float result_2 = round(CalculatePerimeter_test(15)*10000)/10000;
    const float result_3 = round(CalculatePerimeter_test(0)*10000)/10000;
    // Then
    const float expected_1 = 62.8319f;
    const float expected_2 = 94.2478f;
    const float expected_3 = 0.f;

    ASSERT_DBL_NEAR(expected_1, result_1);
    ASSERT_DBL_NEAR(expected_2, result_2);
    ASSERT_DBL_NEAR(expected_3, result_3);
}

CTEST(MATH_LOGIC_TEST_suite,IsCalculatingAreaTrue)// Calculate Area
{
    // When
    const float result_1 = round(CalculateArea_test(10)*10000)/10000;
    const float result_2 = round(CalculateArea_test(15)*10000)/10000;
    const float result_3 = round(CalculateArea_test(0)*10000)/10000; 
    // Then
    const float expected_1 = 314.1593;
    const float expected_2 = 706.8584;
    const float expected_3 = 0.f;  

    ASSERT_DBL_NEAR(expected_1, result_1);
    ASSERT_DBL_NEAR(expected_2, result_2);
    ASSERT_DBL_NEAR(expected_3, result_3);
}

CTEST(PARSING_TEST_suite,isHavingOpenBracketTrue)// open bracket
{
    // Data
    std::string line = "circle(1 2, 3.1)";
    // When
    const bool result = CheckOpenBracket(line); 
    // Then
    const bool expected = true;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingOpenBracketFalse)// no open bracket
{
    // Data
    std::string line = "circle)1 2, 3.1)";
    // When
    const bool result = CheckOpenBracket(line);
    // Then
    const bool expected = false;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingCloseBracketTrue)// close bracket
{
    // Data
    std::string line = "circle(1 2, 3.1)";
    // When
    const bool result = CheckCloseBracket(line);
    // Then
    const bool expected = true;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingCloseBracketFalse)// no close bracket
{
    // Data
    std::string line = "circle(1 2, 3.1(";
    // When
    const bool result = CheckCloseBracket(line);
    // Then
    const bool expected = false;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingRubbishIntoBracketsTrue)// YES rubbish
{
    // Data
    std::string line = "circle(x1 2, 3.0)";
    // When
    const bool result = CheckRubbishInBrackets(line);
    // Then
    const bool expected = false;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingRubbishIntoBracketsFalse)// NO rubbish
{
    // Data
    std::string line = "circle(8 65, 10)";
    // When
    const bool result = CheckRubbishInBrackets(line);
    // Then
    const bool expected = true;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingRubbishOutBracketsTrue)// have rubbish out bracket's
{
    // Data
    std::string line = "circle(1.0 2.1, 3) 123";
    // When
    const bool result = CheckRubbishOutOfBrackets(line);
    // Then
    const bool expected = false;

    ASSERT_EQUAL(expected,result);
}

CTEST(PARSING_TEST_suite,isHavingRubbishOutBracketsFalse)// have't rubbish out bracket's
{
    // Data
    std::string line = "cricle(10.75 14, 15.8)";
    // When
    const bool result = CheckRubbishOutOfBrackets(line);
    // Then
    const bool expected = true;

    ASSERT_EQUAL(expected,result);   
}

CTEST(PARSING_TEST_suite,isBracketsCountExceededTrue)
{
    // Data
    std::string line_1 = "circle((10.75 14, 16)";
    std::string line_2 = "circle(10.75 14, 16)))";
    // When
    const bool result_1 = CheckBracketsCount(line_1);
    const bool result_2 = CheckBracketsCount(line_2);
    // Then
    const bool expected_1 = false;
    const bool expected_2 = false;

    ASSERT_EQUAL(expected_1,result_1);  
    ASSERT_EQUAL(expected_2,result_2);  
}

CTEST(PARSING_TEST_suite,isBracketsCountExceededFalse)
{
    // Data
    std::string line = "circle(10.75 14, 16)";
    // When
    const bool result = CheckBracketsCount(line);
    // Then
    const bool expected = true;

    ASSERT_EQUAL(expected,result);  
}