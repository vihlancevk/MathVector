#include <iostream>
#include <cassert>
#include "UnitTests.hpp"
#include "MathVector.hpp"

void UnitTests() {
    TestOperEquallyEqually();

    TestOperPlus();
    TestOperPlusEqually();
    
    TestOperMinus();
    TestOperPlusMinus();
    TestOperUnaryMinus();

    TestOperMultiplication();
    TestOperMultiplicationEqually();

    TestOperScalarProduct();
}

void TestOperEquallyEqually() {
    Vector vec1(0, 7);
    Vector vec2(-5, 2);
    Vector vec3(0, 7);

    assert((vec1 == vec2) == false);
    assert((vec1 == vec3) == true);
}

void TestOperPlus() {
    Vector vec1(1, 5);
    Vector vec2(-5, 6);
    
    Vector vec3 = vec1 + vec2;
    Vector vec(-4, 11);
    assert(vec3 == vec);
}

void TestOperPlusEqually() {
    Vector vec1(0, -1);
    Vector vec2(1, 0);
    
    vec1 += vec2;
    Vector vec(1, -1);
    assert(vec1 == vec);
}

void TestOperMinus() {
    Vector vec1(15, 8);
    Vector vec2(0, 10);
    
    Vector vec3 = vec1 - vec2;
    Vector vec(15, -2);
    assert(vec3 == vec);
}

void TestOperPlusMinus() {
    Vector vec1(-83, 12);
    Vector vec2(100, -17);
    
    vec1 -= vec2;
    Vector vec(-183, 29);
    assert(vec1 == vec);
}

void TestOperUnaryMinus() {
    Vector vec1(100, -100);
    
    vec1 = -vec1;
    Vector vec(-100, 100);
    assert(vec1 == vec);
}

void TestOperMultiplication() {
    Vector vec(3, 5);
    float f1 = 3;
    float f2 = 0;
    float f3 = -1;

    Vector vec1(9, 15);
    Vector vec12 = f1 * vec;
    assert(vec12 == vec1);
    
    Vector vec2(0, 0);
    Vector vec22 = vec * f2;
    assert(vec22 == vec2);
    
    Vector vec3(-3, -5);
    Vector vec32 = vec * f3;
    assert(vec32 == vec3);
}

void TestOperMultiplicationEqually() {
    Vector vec1(16, 1);
    float f1 = 5;

    Vector vec(80, 5);
    assert((vec1 *= f1) == vec);
}

void TestOperScalarProduct() {
    Vector vec1(3, 5);
    Vector vec2(4, 9);

    assert((int)(vec1 * vec2) == 57);
}
