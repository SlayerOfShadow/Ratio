#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "Rational.h"

TEST (RationalConstructor, defaultConstructor) {
    Rational<int> ratio;
    ASSERT_EQ (ratio.get_numerator(), 0);
    ASSERT_EQ (ratio.get_denominator(), 1);
    ASSERT_EQ (ratio.get_value(), 0);
}

TEST (RationalConstructor, valueConstructor) {
    Rational<int> ratio(3, 2);
    ASSERT_EQ (ratio.get_numerator(), 3);
    ASSERT_EQ (ratio.get_denominator(), 2);
    ASSERT_EQ (ratio.get_value(), double(1.5));

    Rational<int> ratio2(1, 0);
    ASSERT_EQ (ratio2.get_numerator(), 1);
    ASSERT_EQ (ratio2.get_denominator(), 0);
    ASSERT_EQ (ratio2.get_value(), std::numeric_limits<double>::infinity());

    Rational<int> ratio3(-1, 0);
    ASSERT_EQ (ratio3.get_numerator(), -1);
    ASSERT_EQ (ratio3.get_denominator(), 0);
    ASSERT_EQ (ratio3.get_value(), -std::numeric_limits<double>::infinity());
}

TEST (RationalConstructor, copyConstructor) {
    Rational<int> ratio2(3, -6);
    Rational<int> ratio(ratio2);
    ASSERT_EQ (ratio.get_numerator(), -1);
    ASSERT_EQ (ratio.get_denominator(), 2);
    ASSERT_EQ (ratio.get_value(), double(-0.5));
}

TEST (RationalConstructor, realValueConstructor) {
    Rational<int> ratio(0.65f);
    ASSERT_EQ (ratio.get_numerator(), 13);
    ASSERT_EQ (ratio.get_denominator(), 20);
}

TEST (RationalFunction, getters) {
    Rational<int> ratio(4, -7);
    ASSERT_EQ (ratio.get_numerator(), -4);
    ASSERT_EQ (ratio.get_denominator(), 7);
}

TEST (RationalFunction, convertRealToRatio) {
    float real = 0.36f;
    Rational<int> ratio = ratio.convert_real_to_ratio<float>(real, default_nb_iter);
    ASSERT_EQ (ratio.get_numerator(), 18);
    ASSERT_EQ (ratio.get_denominator(), 5);
}

TEST (RationalFunction, reverse) {
    Rational<int> ratio(4, -7);
    Rational<int> ratio2 = ratio.reverse();
    ASSERT_EQ (ratio2.get_numerator(), -7);
    ASSERT_EQ (ratio2.get_denominator(), 4);

    Rational<int> ratio3(0, 5);
    ratio3 = ratio3.reverse();
    ASSERT_EQ (ratio3.get_numerator(), 0);
    ASSERT_EQ (ratio3.get_denominator(), 1);
}

TEST (RationalFunction, pow) {
    Rational<int> ratio(2, 3);
    ratio = ratio.pow(3);
    ASSERT_EQ (ratio.get_numerator(), 8);
    ASSERT_EQ (ratio.get_denominator(), 27);

    Rational<int> ratio2(2, 4);
    ratio2 = ratio2.pow(4);
    ASSERT_EQ (ratio2.get_numerator(), 1);
    ASSERT_EQ (ratio2.get_denominator(), 16);
}

TEST (RationalFunction, sqrt) {
    Rational<int> ratio(4, 9);
    ratio = ratio.sqrt();
    ASSERT_EQ (ratio.get_numerator(), 2);
    ASSERT_EQ (ratio.get_denominator(), 3);
}

TEST (RationalFunction, abs) {
    Rational<int> ratio(4, -7);
    ratio = ratio.abs();
    ASSERT_EQ (ratio.get_numerator(), 4);
    ASSERT_EQ (ratio.get_denominator(), 7);
}

TEST (RationalFunction, floor) {
    Rational<int> ratio(4, -3);
    Rational<int> ratio2(2, 3);
    ASSERT_EQ (ratio.floor(), -2);
    ASSERT_EQ (ratio2.floor(), 0);
}

TEST (RationalFunction, sin) {
    //TODO
}

TEST (RationalFunction, cos) {
    //TODO
}

TEST (RationalFunction, tan) {
    //TODO
}

TEST (RationalFunction, exp) {
    Rational<int> ratio;
    ASSERT_EQ (ratio.exp(), 1);

    Rational<int> ratio2(1, 1);
    ASSERT_NEAR(ratio2.exp(), 2.7, 0.1);
}

TEST (RationalOperator, coutOperator) {
    Rational<int> ratio(3, 4);
    std::stringstream ss;
	ss << ratio;
    ASSERT_EQ (ss.str(), std::to_string(ratio.get_numerator()) + "/" + std::to_string(ratio.get_denominator()));
}

TEST (RationalOperator, equalOperator) {
    Rational<int> ratio(4, 6);
    Rational<int> ratio2 = ratio;
    ASSERT_EQ (ratio2.get_numerator(), 2);
    ASSERT_EQ (ratio2.get_denominator(), 3);
}

TEST (RationalOperator, plusOperator) {
    Rational<int> ratio(4, -6);
    Rational<int> ratio2(5, 3);
    Rational<int> ratio3 = ratio + ratio2;
    ASSERT_EQ (ratio3.get_numerator(), 1);
    ASSERT_EQ (ratio3.get_denominator(), 1);
}

TEST (RationalOperator, plusEqualOperator) {
    Rational<int> ratio(3, 4);
    Rational<int> ratio2(-7, 8);
    ratio2 += ratio;
    ASSERT_EQ (ratio2.get_numerator(), -1);
    ASSERT_EQ (ratio2.get_denominator(), 8);
}

TEST (RationalOperator, unaryMinusArgumentOperator) {
    Rational<int> ratio(4, -3);
    ratio = -ratio;
    ASSERT_EQ (ratio.get_numerator(), 4);
    ASSERT_EQ (ratio.get_denominator(), 3);
}

TEST (RationalOperator, minusOperator) {
    Rational<int> ratio(4, -3);
    Rational<int> ratio2(-2, 7);
    Rational<int> ratio3 = ratio - ratio2;
    ASSERT_EQ (ratio3.get_numerator(), -22);
    ASSERT_EQ (ratio3.get_denominator(), 21);
}

TEST (RationalOperator, minusEqualOperator) {
    Rational<int> ratio(4, -5);
    Rational<int> ratio2(6, -3);
    ratio2 -= ratio;
    ASSERT_EQ (ratio2.get_numerator(), -6);
    ASSERT_EQ (ratio2.get_denominator(), 5);
}

TEST (RationalOperator, multiplyOperator) {
    Rational<int> ratio(4, -3);
    Rational<int> ratio2(-2, 7);
    Rational<int> ratio3 = ratio * ratio2;
    ASSERT_EQ (ratio3.get_numerator(), 8);
    ASSERT_EQ (ratio3.get_denominator(), 21);
}

TEST (RationalOperator, multiplyEqualOperator) {
    Rational<int> ratio(4, -5);
    Rational<int> ratio2(6, -3);
    ratio2 *= ratio;
    ASSERT_EQ (ratio2.get_numerator(), 8);
    ASSERT_EQ (ratio2.get_denominator(), 5);
}

TEST (RationalOperator, divideOperator) {
    Rational<int> ratio(4, 3);
    Rational<int> ratio2(-2, 7);
    Rational<int> ratio3 = ratio / ratio2;
    ASSERT_EQ (ratio3.get_numerator(), -14);
    ASSERT_EQ (ratio3.get_denominator(), 3);
}

TEST (RationalOperator, divideEqualOperator) {
    Rational<int> ratio(4, -5);
    Rational<int> ratio2(6, 3);
    ratio2 /= ratio;
    ASSERT_EQ (ratio2.get_numerator(), -5);
    ASSERT_EQ (ratio2.get_denominator(), 2);
}

TEST (RationalOperator, isEqualOperator) {
    Rational<int> ratio(2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(3, 6);
    ASSERT_EQ (ratio == ratio2, true);
    ASSERT_EQ (ratio == ratio3, false);
}

TEST (RationalOperator, isDifferentOperator) {
    Rational<int> ratio(2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(3, 6);
    ASSERT_EQ (ratio != ratio2, false);
    ASSERT_EQ (ratio != ratio3, true);
}

TEST (RationalOperator, isSuperiorOperator) {
    Rational<int> ratio(2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(-3, 6);
    ASSERT_EQ (ratio > ratio2, false);
    ASSERT_EQ (ratio > ratio3, true);
}

TEST (RationalOperator, isSuperiorOrEqualOperator) {
    Rational<int> ratio(2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(3, 6);
    ASSERT_EQ (ratio >= ratio2, true);
    ASSERT_EQ (ratio >= ratio3, true);
    ASSERT_EQ (ratio3 >= ratio2, false);
}

TEST (RationalOperator, isInferiorOperator) {
    Rational<int> ratio(-2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(3, 6);
    ASSERT_EQ (ratio < ratio2, true);
    ASSERT_EQ (ratio2 < ratio3, false);
}

TEST (RationalOperator, isInferiorOrEqualOperator) {
    Rational<int> ratio(2, 3);
    Rational<int> ratio2(4, 6);
    Rational<int> ratio3(-3, 6);
    ASSERT_EQ (ratio <= ratio2, true);
    ASSERT_EQ (ratio2 <= ratio3, false);
    ASSERT_EQ (ratio3 <= ratio, true);
}