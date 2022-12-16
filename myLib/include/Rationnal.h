#ifndef RATIONNAL_H
#define RATIONNAL_H

#include <iostream>
#include <numeric>
#include <limits>

// Doxygen menu
/// \version 0.1
/// \mainpage
/// \tableofcontents
/// \section instroduction_sec What for?
/// Rationnal is a super tool.
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



/// \class Rationnal
/// \brief class defining a rationnal number for linear algebra operations.
template<typename T, typename U>
class Rationnal
{
    private:
        T m_numerator;
        U m_denominator;
    public:
        Rationnal() : m_numerator(), m_denominator() {}
        Rationnal(T numerator, U denominator) : m_numerator(numerator), m_denominator(denominator)
        {
            int gcd = get_gcd();
            m_numerator /= gcd;
            m_denominator /= gcd; 
        }
        Rationnal(const Rationnal &rationnal) : m_numerator(rationnal.m_numerator), m_denominator(rationnal.m_denominator) {}
        ~Rationnal() {};
        inline T get_numerator() const { return m_numerator; };
        inline U get_denominator() const { return m_denominator; };
        inline int get_gcd() const { return std::gcd(m_numerator, m_denominator); };
        double get_value() const
        {
            return (m_denominator == 0 ? m_numerator * std::numeric_limits<double>::infinity() : double(m_numerator)/m_denominator);
        }
        Rationnal convert_float_to_ratio(float real, uint nb_iter)
        {
            //TODO
        }
};

template<typename T, typename U>
std::ostream& operator<<(std::ostream& stream, const Rationnal<T, U> &rationnal)
{
    return std::cout << "numerator : " << rationnal.get_numerator() << " denominator : " << rationnal.get_denominator() << " value : " << rationnal.get_value() << std::endl;
}

#endif