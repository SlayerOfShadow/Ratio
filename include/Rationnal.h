#ifndef RATIONNAL_H
#define RATIONNAL_H

#include <iostream>
#include <numeric>
#include <limits>

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