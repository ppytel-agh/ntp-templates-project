#include <iostream>

const char* validityString(bool validity) {
    return validity ? "valid" : "INVALID";
}


#define GENERATE_PASCALSTRIANGLE_TESTSTUITE_TEMPLATE_FUNCTION(VALIDITY_FIELD_NAME, VALUE_FIELD_NAME, FIRST_ROW_INDEX, FIRST_COLUMN_INDEX) \
\
template<template<unsigned int, unsigned int> class TestedTemplate, unsigned int a, unsigned int b> \
void testCase(bool expectedValidity, int expectedValue = 0) { \
    std::cout << "TESTCASE TestedTemplate<" << a << ", " << b << ">" << std::endl; \
    std::cout << "validity: expected - " << validityString(expectedValidity) << ", actual - " << validityString(TestedTemplate<a, b>::VALIDITY_FIELD_NAME) << std::endl; \
    std::cout << "value: expected - " << expectedValue << ", actual - " << TestedTemplate<a, b>::VALUE_FIELD_NAME << std::endl; \
    bool testResult = (expectedValidity == TestedTemplate<a, b>::VALIDITY_FIELD_NAME) && (expectedValue == TestedTemplate<a, b>::VALUE_FIELD_NAME); \
    std::cout << "test " << (testResult ? "SUCCEEDED" : "FAILED") << std::endl << std::endl; \
} \
\
template<template<unsigned int, unsigned int> class TestedTemplate > \
void pascalsTriangleTestSuite() { \
    const int preFirstRowIndex = FIRST_ROW_INDEX - 1; \
    const int secondColumnIndex = FIRST_COLUMN_INDEX +  1; \
    const int thirdRowIndex = FIRST_ROW_INDEX + 2; \
    const int eighthRowIndex = FIRST_ROW_INDEX + 7; \
    const int thirdColumnIndex = FIRST_COLUMN_INDEX + 2; \
    testCase<TestedTemplate, FIRST_ROW_INDEX, FIRST_COLUMN_INDEX>(true, 1); \
    testCase<TestedTemplate, preFirstRowIndex, FIRST_COLUMN_INDEX>(false); \
    testCase<TestedTemplate, FIRST_ROW_INDEX, secondColumnIndex>(false); \
    testCase<TestedTemplate, thirdRowIndex, secondColumnIndex>(true, 2); \
    testCase<TestedTemplate, eighthRowIndex, thirdColumnIndex>(true, 21); \
}
