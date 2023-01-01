#ifndef Rational_H
#define Rational_H

#include <iostream>
#include <numeric>
#include <limits>
#include <cmath>

// Doxygen menu
/// \version 0.1
/// \mainpage
/// \image html Image.png
/// \tableofcontents
/// \section introduction_sec What for?
/// Rational is a super tool made by Antoine Leblond and Mathurin Rambaud in order to convert real values into human readable fration
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependencies
/// \li STL
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
/// \section use_sec How to use
/// \li A demo is available at /build/myCode/main to explain you how it works
/// \section credits_sec Credits
/// \li Thanks to our teacher Vincent Nozick who shared us his knowledge in order to achieve this project

int default_nb_iter = 10;
float default_error_value = 1e-4;

/// \class Rational
/// \brief class defining a Rational number for linear algebra operations
template<typename T = int>
class Rational
{
    public:
        //constructors

        /// \brief default constructor with value of 0/1
		/// \tparam T : int
        constexpr Rational<T>() : m_numerator(0), m_denominator(1) 
        {
            static_assert(std::is_integral_v<T>, "type must be int");
        }

        /// \brief value constructor giving an irreducible fraction
		/// \tparam T : int
		/// \param numerator : numerator
		/// \param denominator : denominator
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

        /// \brief copy constructor
		/// \tparam T : int
		/// \param ratio : Rational we want to copy the value from
        constexpr Rational<T>(const Rational& ratio) : m_numerator(ratio.m_numerator), m_denominator(ratio.m_denominator) {}

        /// \brief real value constructor
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : real value that needs to be converted
        template<typename U>
        constexpr Rational<T>(const U& var)
        {
            *this = convert_real_to_ratio(var, default_nb_iter);
        }

        /// \brief default destructor
        ~Rational() = default;

    private:
        T m_numerator; /**< Rational numerator */
        T m_denominator; /**< Rational denominator */

    public:
        //Functions

        /// \brief return numerator of type T
        constexpr inline T get_numerator() const { return m_numerator; };

        /// \brief return denominator of type T
        constexpr inline T get_denominator() const { return m_denominator; };

        /// \brief set numerator with a value
        /// \tparam T : int
        /// \param var : variable that need to be the numerator
        constexpr inline void set_numerator(T var) { m_numerator = var; };

        /// \brief set denominator with a value
        /// \tparam T : int
        /// \param var : variable that need to be the denominator
        constexpr inline void set_denominator(T var) { m_denominator = var; };

        /// \brief return the greatest common divisor of numerator and denominator
        constexpr inline int get_gcd() const { return std::gcd(m_numerator, m_denominator); };

        /// \brief return the float value of the fraction, if denominator equals 0 either return inf or -inf depending on the sign of the numerator
        constexpr float get_value() const
        {
            return (m_denominator == 0 ? m_numerator * std::numeric_limits<float>::infinity() : float(m_numerator)/m_denominator);
        }

        /// \brief return the sign of an int which is -1 or 1, used to make denominator always positive
        /// \tparam T : int
        /// \param val : value we want the sign of
        constexpr int get_sign(T val) const
        {
            return (T(0) <= val) - (val < T(0));
        }

        /// \brief convert a real into a Rational
        /// \tparam T : int
        /// \tparam U : int, floating point or Rational
        /// \param real : value we want to convert
        /// \param nb_iter : define the number of iterations for the recursive function, the more there are the more precise it is
        template<typename U>
        constexpr Rational<T> convert_real_to_ratio(const U& real, const uint nb_iter) const
        {
            if constexpr (std::is_same_v<U, Rational>)
            {
                return real;
            } 
            else if constexpr (std::is_integral_v<U>)
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
                    return (convert_real_to_ratio<U>(1 / real, nb_iter)).reverse();
                }
                
                U real_integer_part = std::floor(real_absolute_value);
                U floating_part = real_absolute_value - real_integer_part;
                if (floating_part < default_error_value) //else numerator and denominator get crazy values
                {
                    floating_part = 0;
                }
                return Rational<T>(get_sign(real) * real_integer_part, 1) + convert_real_to_ratio<U>(get_sign(real) * floating_part, nb_iter - 1);
            }
            else
            {
                throw std::invalid_argument("unable to convert this type");
            }
        }

        /// \brief return the reverse of a fraction (a/b returns b/a), though denominator can't be equal to 0
        constexpr Rational<T> reverse() const
        {
            if (m_denominator == 0)
            {
				throw std::invalid_argument("denominator can't be equal to 0");
			}

            if (m_numerator != 0)
            {
                return Rational<T> (m_denominator * get_sign(m_numerator), m_numerator * get_sign(m_numerator));
            } 
            else 
            {
                return Rational<T>();
            }
        }

        /// \brief recursive function that calculates the power of a Rational, returns 0 if numerator equals to 0
        /// \param n : the power
        constexpr Rational<T> pow(const uint& n) const
        {
            return (n != 0 ? Rational<T>(m_numerator, m_denominator) * pow(n - 1) : Rational<T>(1, 1));
        }

        /// \brief return the square root of a Rational, though must be positive
        constexpr Rational<T> sqrt() const
        {
            if (m_numerator < 0)
            {
                throw std::invalid_argument("value must be positive");
            }
            return Rational<T>(std::sqrt(m_numerator), std::sqrt(m_denominator));
        }

        /// \brief return the absolute value of a Rational
        constexpr Rational<T> abs() const
        {
            return Rational<T>(std::abs(m_numerator), m_denominator);
        }

        /// \brief return the floor of a Rational
        constexpr int floor() const
        {
            return std::floor(get_value());
        }

        /// \brief return the sinus of a Rational
        constexpr float sin() const
        {
            return std::sin(get_value());
        }

        /// \brief return the cosinus of a Rational
        constexpr float cos() const
        {
            return std::cos(get_value());
        }

        /// \brief return the tangent of a Rational
        constexpr float tan() const
        {
            return std::tan(get_value());
        }

        /// \brief return the exponential of a Rational
        constexpr float exp() const
        {
            return std::exp(get_value());
        }

        /// \brief return the minimum value between two Rational
        /// \tparam T : int
        /// \param ratio1 : first Rational
        /// \param ratio1 : second Rational
        constexpr Rational<T> min(const Rational<T>& ratio1, const Rational<T> ratio2) const
        {
            return (ratio1 < ratio2 ? ratio1 : ratio2);
        }

        /// \brief return the minimum value between multiple Rational
        /// \tparam T : int
        /// \param ratio1 : first Rational
        /// \param args : the others
        template<typename... Args>
        constexpr Rational<T> min(const Rational<T>& ratio, const Args... args) const
        {
            return min(ratio, min(args...));
        }

        /// \brief return the maximum value between two Rational
        /// \tparam T : int
        /// \param ratio1 : first Rational
        /// \param ratio1 : second Rational
        constexpr Rational<T> max(const Rational<T>& ratio1, const Rational<T> ratio2) const
        {
            return (ratio1 > ratio2 ? ratio1 : ratio2);
        }


        /// \brief return the maximum value between multiple Rational
        /// \tparam T : int
        /// \param ratio1 : first Rational
        /// \param args : the others
        template<typename... Args>
        constexpr Rational<T> max(const Rational<T>& ratio, const Args... args) const
        {
            return max(ratio, max(args...));
        }

        //Operators

        /// \brief affectation operator
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want the value of 
        template<typename U>
        constexpr void operator=(const U& var)
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            m_numerator = ratio.get_numerator();
            m_denominator = ratio.get_denominator();
        }

        /// \brief sum of 2 Rational
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to sum with
        template<typename U>
        constexpr Rational<T> operator+(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return Rational<T>(m_numerator * ratio.get_denominator() + m_denominator * ratio.get_numerator(),
                                m_denominator * ratio.get_denominator());
        }

        /// \brief add a Rational with the called Rational and affect it
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to sum with the called Rational
        template<typename U>
        constexpr void operator+=(const U& var)
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            *this = *this + ratio;
        }

        /// \brief unary minus operator
        /// \tparam T : int
        constexpr Rational<T> operator-() const
        {
            return Rational<T>(-1 * m_numerator, m_denominator);
        }

        /// \brief subtraction of 2 Rational
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to substract with
        template<typename U>
        constexpr Rational<T> operator-(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return Rational<T>(m_numerator * ratio.get_denominator() - m_denominator * ratio.get_numerator(),
                                m_denominator * ratio.get_denominator());
        }

        /// \brief substract a Rational with the called Rational and affect it
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to substract with the called Rational
        template<typename U>
        constexpr void operator-=(const U& var)
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            *this = *this - ratio;
        }

        /// \brief multiplication of 2 Rational
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to multiply with
        template<typename U>
        constexpr Rational<T> operator*(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return Rational<T>(m_numerator * ratio.get_numerator(), m_denominator * ratio.get_denominator());
        }

        /// \brief multiply a Rational with the called Rational and affect it
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to multiply with the called Rational
        template<typename U>
        constexpr void operator*=(const U& var)
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            *this = *this * ratio;
        }
        
        /// \brief division of 2 Rational
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to divide with
        template<typename U>
        constexpr Rational<T> operator/(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return *this * ratio.reverse();
        }

        /// \brief divide a Rational with the called Rational and affect it
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to divide with the called Rational
        template<typename U>
        constexpr void operator/=(const U& var)
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            *this = *this / ratio;
        }

        /// \brief compare if a Rational is equal from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator==(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator == ratio.get_numerator() && m_denominator == ratio.get_denominator());
        }

        /// \brief compare if a Rational is different from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator!=(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator != ratio.get_numerator() || m_denominator != ratio.get_denominator());
        }

        /// \brief compare if a Rational is superior from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator>(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator * ratio.get_denominator() > m_denominator * ratio.get_numerator());
        }

        /// \brief compare if a Rational is superior or equal from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator>=(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator * ratio.get_denominator() >= m_denominator * ratio.get_numerator());
        }

        /// \brief compare if a Rational is inferior from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator<(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator * ratio.get_denominator() < m_denominator * ratio.get_numerator());
        }

        /// \brief compare if a Rational is inferior or equal from another, return true if so else return false
		/// \tparam T : int
		/// \tparam U : int, floating point or Rational
		/// \param var : the variable we want to compare with
        template<typename U>
        constexpr bool operator<=(const U& var) const
        {
            Rational<T> ratio = convert_real_to_ratio<U>(var, default_nb_iter);
            return (m_numerator * ratio.get_denominator() <= m_denominator * ratio.get_numerator());
        }
};

/// \brief display a Rational with a human readable form
/// \tparam T : int
/// \param ratio : the Rational we want to display
template<typename T = int>
std::ostream& operator<<(std::ostream& stream, const Rational<T>& ratio)
{
    stream << ratio.get_numerator() << "/" << ratio.get_denominator();
    return stream;
}

#endif