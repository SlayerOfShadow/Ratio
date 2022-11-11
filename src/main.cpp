#include "../include/Rationnal.h"

int main()
{
    Rationnal number(-5, 0);
    Rationnal number2(number);
    std::cout << number2 << std::endl;
    return 0;
}