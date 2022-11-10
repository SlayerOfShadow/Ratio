#ifndef RATIONNAL_H
#define RATIONNAL_H

#include <iostream>

template<typename T>
class Rationnal
{
    private:
        T m_numerator;
        T m_denominator;
    public:
        Rationnal() : m_numerator(), m_denominator() {}
        Rationnal(T numerator, T denominator) : m_numerator(numerator), m_denominator(denominator) {}
        Rationnal(const Rationnal &rationnal) : m_numerator(rationnal.m_numerator), m_denominator(rationnal.m_denominator) {}
        ~Rationnal() {};
        inline T get_numerator() const { return m_numerator; };
        inline T get_denominator() const { return m_denominator; };
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Rationnal<T> &rationnal)
{
    return std::cout << "numerator : " << rationnal.get_numerator() << " denominator : " << rationnal.get_denominator() << std::endl;
}

#endif