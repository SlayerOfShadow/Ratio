#include <iostream>

#include "Rational.h"

int main()
{
    Rational number = Rational<int>(5, -2);
    Rational number2 = Rational<int>(number);
    std::cout << number2 << std::endl;
    return 0;
}