#include <iostream>
#include <cstdio>

#include "Rational.h"

int main()
{
    system("clear");

    std::cout << "This library was made by Antoine Leblond and Mathurin Rambaud.\n" << std::endl;
    std::cout << "Please see the documentation on Doxygen before using it." << std::endl;
    std::cout << "This is a demo to show you how can you use it. \nEnjoy!" << std::endl;
    
    std::cout << "\nEnter a key to continue..." << std::endl;
    char k;
    std::cin >> k;
    system("clear");
    
    std::cout << "The main goal of this library is to be able to represent floating point number into human readable functions and therefore do linear algebra operations on them." << std::endl;
    std::cout << "Indeed, if you want to represent the following sequence : " << std::endl;
    std::cout << "\nu(0) = 1/3     u(n+1) = 4u(n)-1\n" << std::endl;
    std::cout << "We all know that normally this sequence will always give 1/3. However, if you try this on a computer with double you'll notice that the sequence starts to diverge." << std::endl;
    std::cout << "So instead of directly applying operations to the real value we will first convert it to a Rational number with a numerator and a denominator, do the operations\nand then only at the end eventually display a real value of it." << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "You declare a Rational by typing :\n\nRational<int> my_rational;\n" << std::endl;
    std::cout << "Note that in this case I did not precised the numerator and the denominator so the default value is 0/1." << std::endl;
    std::cout << "Moreover you have to know that this class only supports integers for the numerator and denominator. For example :\n\nRational<int> my_rational(3,5); works\nRational<float> my_rational(3.2f,5.6f); doesn't work." << std::endl;
    std::cout << "\nNotice that you can also create negative Rational, yet the denominator will always be positive :\n\nRational<int> my_rational(3,-5); corresponds to -3/5\nRational<int> my_rational(-3,-5); corresponds to 3/5" << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "Thanks to the function convert_real_to_ratio() you can also create a Rational from a real value." << std::endl;
    std::cout << "\nRational<int> my_rational(8.4f); will create an irreducible Rational, in this case 42/5.\n" << std::endl;
    std::cout << "You can also obviously create a Rational from another :\n\nRational<int> my_rational(my_other_rational); will create a rational with the same numerator and denominator." << std::endl;
    std::cout << "\nNote that you can get the float value of a Rational at anytime you want by using the function get_value() :" << std::endl;
    std::cout << "\nRational<int> my_rational(5, 4);\nmy_rational.get_value(); will return 1.25" << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "This library brings a bunch of functions, for exemple you can reverse a Rational :" << std::endl;
    std::cout << "\nRational<int> my_rational(4, -7);\nmy_rational = my_rational.reverse(); will give -7/4" << std::endl;
    std::cout << "\nYou can do the square root of a Rational :" << std::endl;
    std::cout << "\nRational<int> my_rational(4, 9); \nmy_rational = my_rational.sqrt(); will give you 2/3" << std::endl;
    std::cout << "\nOr calculate the power of a Rational with a recursive function :" << std::endl;
    std::cout << "\nRational<int> my_rational(2, 4); \nmy_rational = my_rational.pow(4); will give you 1/16" << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "Absolute value function :" << std::endl;
    std::cout << "\nRational<int> my_rational(4, -7);\nmy_rational = my_rational.abs(); will give 4/7" << std::endl;
    std::cout << "\nYou also have functions that directly apply to the real value of the Rational. For example floor, sinus, cosinus, tangent, exp..." << std::endl;
    std::cout << "Yet for some you'll have to use convert_real_to_ratio() since some of them use PI." << std::endl;
    std::cout << "\nRational<int> my_rational(4, -3);\nmy_rational.floor(); will give -2" << std::endl;
    std::cout << "\nRational<int> my_rational2(1, 1);\nmy_rational2.exp(); will give ~2.7" << std::endl;
    std::cout << "\nRational<int> my_rational = my_rational.convert_real_to_ratio<double>(M_PI/3, default_nb_iter); default_nb_iter controls the precision" << std::endl;
    std::cout << "ratio.sin(); will give ~0.866 that corresponds to sqrt(3)/2\nratio.cos(); will give ~0.5 that corresponds to 1/2\nratio.tan(); will give ~1.732 since it's sin/cos" << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "Also this library comes with two variadic functions that allows you to determine the minimum and the maximum value between many :" << std::endl;
    std::cout << "\nRational<int> my_rational1(8, 9);\nRational<int> my_rational2(-1, 1);\nRational<int> my_rational3(5, 3);\n\nmy_rational1.min(my_rational1, my_rational2, my_rational3); will return my_rational2\nmy_rational1.max(my_rational1, my_rational2, my_rational3); will return my_rational3" << std::endl;
    
    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "Finally this library comes with a bunch of arithmetic, assignment and relational operators." << std::endl;
    std::cout << "Note that you can compare a Rational with a real value it will still works :" << std::endl;
    std::cout << "\nRational<int> my_rational1(4, -6);\nRational<int> my_rational2(5, 3);\nRational<int> my_rational3 = my_rational1 + my_rational2; will give 1/1" << std::endl;
    std::cout << "\nRational<int> my_rational1(3, 4);\nRational<int> my_rational2 = my_rational1 * 3.26; will give 489/200" << std::endl;
    std::cout << "\nRational<int> my_rational1(4, -5);\nRational<int> my_rational2(6, 3);\nmy_rational2 /= my_rational1; will give -5/2" << std::endl;
    std::cout << "\nRational<int> my_rational(-6, 2);\nint my_int = -3;\nmy_rational < my_int; will return false" << std::endl;

    std::cout << "\nEnter a key to continue..." << std::endl;
    std::cin >> k;
    system("clear");

    std::cout << "Well that's pretty much it ! I hope this demo helped you understand how to use this library." << std::endl;
    std::cout << "Again we highly recommand you to check the Doxygen documentation which you can find in /build/INTERFACE/doc/doc-doxygen/index.html" << std::endl;
    std::cout << "\nThanks again and have fun using Rational !" << std::endl;

    std::cout << "\nEnter a key to end this demo !" << std::endl;
    std::cin >> k;

    return 0;
}