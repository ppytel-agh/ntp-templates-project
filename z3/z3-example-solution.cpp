#include "testsuite.hpp"

template<unsigned int row,unsigned int column>
struct PascalsTriangle {
    static const bool valid = (row > 0) && (column > 0 && column <= row);
    static const int value = PascalsTriangle<row-1, column>::value + PascalsTriangle<row-1, column-1>::value;    
};

template<unsigned int column>
struct PascalsTriangle <0, column> {
    static const bool valid = false;
    static const int value = 0;
};

template<unsigned int row>
struct PascalsTriangle <row, 0> {
    static const bool valid = false;
    static const int value = 0;
};

template<>
struct PascalsTriangle<1, 1> {
    static const bool valid = true;
    static const int value = 1;
};

GENERATE_PASCALSTRIANGLE_TESTSTUITE_TEMPLATE_FUNCTION(valid, value, 1, 1)

int main() {
    pascalsTriangleTestSuite<PascalsTriangle>();
}