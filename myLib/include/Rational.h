#ifndef Rational_H
#define Rational_H

#include <iostream>
#include <numeric>
#include <limits>
#include <cmath>

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

int default_nb_iter = 5;

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

        template<typename U>
        constexpr Rational<T>(const U& var)
        {
            *this = convert_real_to_ratio(var, default_nb_iter);
        }

        ~Rational() = default;

    private:
        T m_numerator;
        T m_denominator;

    public:
        //Functions
        constexpr inline T get_numerator() const { return m_numerator; };

        constexpr inline T get_denominator() const { return m_denominator; };

        constexpr inline void set_numerator(T var) { m_numerator = var; };

        constexpr inline void set_denominator(T var) { m_denominator = var; };

        constexpr inline int get_gcd() const { return std::gcd(m_numerator, m_denominator); };

        constexpr float get_value() const
        {
            return (m_denominator == 0 ? m_numerator * std::numeric_limits<float>::infinity() : float(m_numerator)/m_denominator);
        }

        constexpr int get_sign(T val) const
        {
            return (T(0) <= val) - (val < T(0));
        }

        template<typename U>
        constexpr Rational<T> convert_real_to_ratio(const U& real, const uint nb_iter)
        {
            if (std::is_same_v<U, Rational>)
            {
                return real;
            } 
            else if (std::is_integral_v<U>)
            {
                return Rational<T>(real, 1);
            }
            else if constexpr (std::is_floating_point_v<U>)
            {
                U real_absolute_value = std::abs(real);
            
                if (real_absolute_value == 0 || nb_iter == 0)
                {
                    return Rational<T>();
                }

                if (real_absolute_value < 1)
                {
                    return (convert_real_to_ratio<U>(U(1*get_sign(real)/real_absolute_value), nb_iter)).reverse();
                }
                
                U real_integer_part = std::floor(real_absolute_value);
                U floating_part = real_absolute_value - real_integer_part;
                if (floating_part<1e-10) floating_part=0;
                return Rational<T>(T(get_sign(real)) * real_integer_part, T(1)) + convert_real_to_ratio<U>(U(get_sign(real))*floating_part, nb_iter - 1);
            }
            else
            {
                throw std::invalid_argument("unable to convert this type");
            }
        }

        constexpr Rational<T> reverse() const
        {
            if (m_denominator == 0){
				throw std::invalid_argument("denominator can't be equal to 0");
			}

            if (m_numerator != 0)
            {
                Rational<T> ratio(m_denominator * get_sign(m_numerator), m_numerator * get_sign(m_numerator));
                return ratio;
            } else {
                Rational<T> ratio2(0, 1);
                return ratio2;
            }
        }

        constexpr Rational<T> pow(const uint& n) const
        {
            return (n != 0 ? Rational<T>(m_numerator, m_denominator) * pow(n - 1) : Rational<T>(1, 1));
        }

        constexpr Rational<T> sqrt() const
        {
            if (m_numerator < 0)
            {
                throw std::invalid_argument("value must be positive");
            }
            return Rational<T>(std::sqrt(m_numerator), std::sqrt(m_denominator));
        }

        constexpr Rational<T> abs() const
        {
            return Rational<T>(std::abs(m_numerator), m_denominator);
        }

        constexpr int floor() const
        {
            return std::floor(get_value());
        }

        constexpr float sin() const
        {
            return std::sin(get_value());
        }

        constexpr float cos() const
        {
            return std::cos(get_value());
        }

        constexpr float tan() const
        {
            return std::tan(get_value());
        }

        constexpr float exp() const
        {
            return std::exp(get_value());
        }

        //Operators
        constexpr void operator=(const Rational<T>& ratio)
        {
            m_numerator = ratio.get_numerator();
            m_denominator = ratio.get_denominator();
        }

        constexpr Rational<T> operator+(const Rational<T>& ratio) const
        {
            return Rational<T>(m_numerator * ratio.get_denominator() + m_denominator * ratio.get_numerator(),
                                m_denominator * ratio.get_denominator());
        }

        constexpr void operator+=(const Rational<T>& ratio)
        {
            *this = *this + ratio;
        }

        constexpr Rational<T> operator-() const
        {
            return Rational<T>(-1 * m_numerator, m_denominator);
        }

        constexpr Rational<T> operator-(const Rational<T>& ratio) const
        {
            return Rational<T>(m_numerator * ratio.get_denominator() - m_denominator * ratio.get_numerator(),
                                m_denominator * ratio.get_denominator());
        }

        constexpr void operator-=(const Rational<T>& ratio)
        {
            *this = *this - ratio;
        }

        constexpr Rational<T> operator*(const Rational<T>& ratio) const
        {
            return Rational<T>(m_numerator * ratio.get_numerator(), m_denominator * ratio.get_denominator());
        }

        constexpr void operator*=(const Rational<T>& ratio)
        {
            *this = *this * ratio;
        }
        
        constexpr Rational<T> operator/(const Rational<T>& ratio) const
        {
            return *this * ratio.reverse();
        }

        constexpr void operator/=(const Rational<T>& ratio)
        {
            *this = *this / ratio;
        }

        constexpr bool operator==(const Rational<T>& ratio) const
        {
            return (m_numerator == ratio.get_numerator() && m_denominator == ratio.get_denominator());
        }

        constexpr bool operator!=(const Rational<T>& ratio) const
        {
            return (m_numerator != ratio.get_numerator() || m_denominator != ratio.get_denominator());
        }

        constexpr bool operator>(const Rational<T>& ratio) const
        {
            return (m_numerator * ratio.get_denominator() > m_denominator * ratio.get_numerator());
        }

        constexpr bool operator>=(const Rational<T>& ratio) const
        {
            return (m_numerator * ratio.get_denominator() >= m_denominator * ratio.get_numerator());
        }

        constexpr bool operator<(const Rational<T>& ratio) const
        {
            return (m_numerator * ratio.get_denominator() < m_denominator * ratio.get_numerator());
        }

        constexpr bool operator<=(const Rational<T>& ratio) const
        {
            return (m_numerator * ratio.get_denominator() <= m_denominator * ratio.get_numerator());
        }
};

template<typename T = int>
std::ostream& operator<<(std::ostream& stream, const Rational<T>& ratio)
{
    stream << ratio.get_numerator() << "/" << ratio.get_denominator();
    return stream;
}

#endif