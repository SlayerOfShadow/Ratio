#include <gtest/gtest.h>
#include "Rational.h"

TEST (RationalConstructor, defaultConstructor) {
    Rational<int> ratio;
    EXPECT_EQ (ratio.get_numerator(), 0);
    EXPECT_EQ (ratio.get_denominator(), 1);
    EXPECT_EQ (ratio.get_value(), 0);
}

TEST (RationalConstructor, valueConstructor) {
    Rational<int> ratio(3, 2);
    EXPECT_EQ (ratio.get_numerator(), 3);
    EXPECT_EQ (ratio.get_denominator(), 2);
    EXPECT_EQ (ratio.get_value(), double(1.5));

    Rational<int> ratio2(1, 0);
    EXPECT_EQ (ratio2.get_numerator(), 1);
    EXPECT_EQ (ratio2.get_denominator(), 0);
    EXPECT_EQ (ratio2.get_value(), std::numeric_limits<double>::infinity());

    Rational<int> ratio3(-1, 0);
    EXPECT_EQ (ratio3.get_numerator(), -1);
    EXPECT_EQ (ratio3.get_denominator(), 0);
    EXPECT_EQ (ratio3.get_value(), -std::numeric_limits<double>::infinity());
}

TEST (RationalConstructor, copyConstructor) {
    Rational<int> ratio2(3, -6);
    Rational<int> ratio(ratio2);
    EXPECT_EQ (ratio.get_numerator(), -1);
    EXPECT_EQ (ratio.get_denominator(), 2);
    EXPECT_EQ (ratio.get_value(), double(-0.5));
}

TEST (RationalFunction, getters) {
    Rational<int> ratio(4, -7);
    EXPECT_EQ (ratio.get_numerator(), -4);
    EXPECT_EQ (ratio.get_denominator(), 7);
}