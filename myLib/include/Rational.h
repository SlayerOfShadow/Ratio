#ifndef Rational_H
#define Rational_H

#include <iostream>
#include <numeric>
#include <limits>

// Doxygen menu
/// \version 0.1
/// \mainpage
/// \tableofcontents
/// \section instroduction_sec What for?
/// Rational is a super tool.
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li nothing
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux / Mac)
/// \li go to main dir
/// \li mkdir build
/// \li cd build
/// \li cmake ..
/// \li make
/// \li if Doxygen installed: make html
/// \li The documentation is located in :
/// 	- [path to build]/doc/doc-doxygen/html/index.html or 
/// 	- or [path to build]/INTERFACE/doc/doc-doxygen/html/index.html



/// \class Rational
/// \brief class defining a Rational number for linear algebra operations.
template<typename T = int>
class Rational
{
    public:
        //constructors
        constexpr Rational<T>() : m_numerator(0), m_denominator(1) 
        {
            static_assert(std::is_integral_v<T>, "type must be int");
        }
        constexpr Rational<T>(const T& numerator, const T& denominator) : m_numerator(numerator), m_denominator(denominator)
        {
            static_assert(std::is_integral_v<T>, "type must be int");
            if (m_numerator == 0 && m_denominator == 0)
            {
			    throw std::invalid_argument("numerator and denominator can't be equal to 0");
		    }

            int gcd = get_gcd();
            if (gcd != 1)
            {
                m_numerator /= gcd;
                m_denominator /= gcd;
		    }
            
            m_numerator *= get_sign(m_denominator);
            m_denominator *= get_sign(m_denominator);
        }
        constexpr Rational<T>(const Rational& ratio) : m_numerator(ratio.m_numerator), m_denominator(ratio.m_denominator) {}
        ~Rational() = default;
    private:
        T m_numerator;
        T m_denominator;
    public:
        constexpr inline T get_numerator() const { return m_numerator; };
        constexpr inline T get_denominator() const { return m_denominator; };
        constexpr inline int get_gcd() const { return std::gcd(m_numerator, m_denominator); };
        constexpr double get_value() const
        {
            return (m_denominator == 0 ? m_numerator * std::numeric_limits<double>::infinity() : double(m_numerator)/m_denominator);
        }
        constexpr int get_sign(T val)
        {
            return (T(0) <= val) - (val < T(0));
        }
        constexpr Rational convert_float_to_ratio(float real, uint nb_iter)
        {
            //TODO
        }
};

template<typename T = int>
std::ostream& operator<<(std::ostream& stream, const Rational<T>& ratio)
{
    return std::cout << "numerator : " << ratio.get_numerator() << " denominator : " << ratio.get_denominator() << " value : " << ratio.get_value() << std::endl;
}

#endif