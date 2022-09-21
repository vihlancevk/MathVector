#ifndef UNIT_TESTS_HPP_
#define UNIT_TESTS_HPP_

void UnitTests();

void TestOperEquallyEqually(); // lhs == rhs

void TestOperPlus(); // res = lhs + rhs
void TestOperPlusEqually(); // lhs += rhs

void TestOperMinus(); // res = lhs - rhs
void TestOperPlusMinus(); // lhs -= rhs
void TestOperUnaryMinus(); // lhs = -lhs

void TestOperMultiplication(); // res = f * rhs or res = lhs * f
void TestOperMultiplicationEqually(); // lhs *= f

void TestOperScalarProduct(); // f = lhs * rhs

#endif // UNIT_TESTS_HPP_