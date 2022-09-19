#include <iostream>
#include <cassert>
#include "UnitTests.hpp"
#include "Vector.hpp"

void UnitTests() {
    TestOperPlus();
    TestOperPlusEqually();
    
    TestOperMinus();
    TestOperPlusMinus();
    TestOperUnaryMinus();
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
