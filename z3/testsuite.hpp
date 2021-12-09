#include <iostream>

const char* validityString(bool validity) {
    return validity ? "valid" : "INVALID";
}

template<template<unsigned int, unsigned int> class TestedTemplate, unsigned int a, unsigned int b>
void testCase(bool expectedValidity, int expectedValue = 0) {
    std::cout << "TESTCASE TestedTemplate<" << a << ", " << b << ">" << std::endl;
    std::cout << "validity: expected - " << validityString(expectedValidity) << ", actual - " << validityString(TestedTemplate<a, b>::valid) << std::endl;
    std::cout << "value: expected - " << expectedValue << ", actual - " << TestedTemplate<a, b>::value << std::endl;
    bool testResult = (expectedValidity == TestedTemplate<a, b>::valid) && (expectedValue == TestedTemplate<a, b>::value);
    std::cout << "test " << (testResult ? "SUCCEEDED" : "FAILED") << std::endl << std::endl;
}

template<template<unsigned int, unsigned int> class TestedTemplate >
void pascalsTriangleTestSuite() {
    testCase<TestedTemplate, 1,1>(true, 1);
    testCase<TestedTemplate, 0,1>(false);
    testCase<TestedTemplate, 1,2>(false);
    testCase<TestedTemplate, 3,2>(true, 2);
    testCase<TestedTemplate, 8,3>(true, 21);
}