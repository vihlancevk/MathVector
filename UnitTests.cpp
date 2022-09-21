#include <iostream>
#include <cassert>
#include "UnitTests.hpp"
#include "Vector.hpp"

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
    Vector vec1 = Vector(0, 7);
    Vector vec2 = Vector(-5, 2);
    Vector vec3 = Vector(0, 7);

    assert((vec1 == vec2) == false);
    assert((vec1 == vec3) == true);
}

void TestOperPlus() {
    Vector vec1 = Vector(1, 5);
    Vector vec2 = Vector(-5, 6);
    
    Vector vec3 = vec1 + vec2;
    assert(vec3 == Vector(-4, 11));
}

void TestOperPlusEqually() {
    Vector vec1 = Vector(0, -1);
    Vector vec2 = Vector(1, 0);
    
    vec1 += vec2;
    assert(vec1 == Vector(1, -1));
}

void TestOperMinus() {
    Vector vec1 = Vector(15, 8);
    Vector vec2 = Vector(0, 10);
    
    Vector vec3 = vec1 - vec2;
    assert(vec3 == Vector(15, -2));
}

void TestOperPlusMinus() {
    Vector vec1 = Vector(-83, 12);
    Vector vec2 = Vector(100, -17);
    
    vec1 -= vec2;
    assert(vec1 == Vector(-183, 29));
}

void TestOperUnaryMinus() {
    Vector vec1 = Vector(100, -100);
    
    vec1 = -vec1;
    assert(vec1 == Vector(-100, 100));
}

void TestOperMultiplication() {
    Vector vec = Vector(3, 5);
    float f1 = 3;
    float f2 = 0;
    float f3 = -1;

    assert(f1 * vec == Vector(9, 15));
    assert(vec * f2 == Vector(0, 0));
    assert(vec * f3 == Vector(-3, -5));
}

void TestOperMultiplicationEqually() {
    Vector vec1 = Vector(16, 1);
    float f1 = 5;

    assert((vec1 *= f1) == Vector(80, 5));
}

void TestOperScalarProduct() {
    Vector vec1 = Vector(3, 5);
    Vector vec2 = Vector(4, 9);

    assert((int)(vec1 * vec2) == 57);
}
