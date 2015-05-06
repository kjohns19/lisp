#include <lisp/util/BigNumber.hpp>

namespace lisp
{

BigNumber::BigNumber(long value):
    d_value(value) {}

long BigNumber::getValue() const
{
    return d_value;
}

BigNumber operator+(const BigNumber& n1, const BigNumber& n2)
{
    return BigNumber(n1.getValue() + n2.getValue());
}
BigNumber operator-(const BigNumber& n1, const BigNumber& n2)
{
    return BigNumber(n1.getValue() - n2.getValue());
}
BigNumber operator*(const BigNumber& n1, const BigNumber& n2)
{
    return BigNumber(n1.getValue() * n2.getValue());
}
BigNumber operator/(const BigNumber& n1, const BigNumber& n2)
{
    return BigNumber(n1.getValue() / n2.getValue());
}
BigNumber operator%(const BigNumber& n1, const BigNumber& n2)
{
    return BigNumber(n1.getValue() % n2.getValue());
}

BigNumber operator+(long n1, const BigNumber& n2)
{
    return BigNumber(n1 + n2.getValue());
}
BigNumber operator-(long n1, const BigNumber& n2)
{
    return BigNumber(n1 - n2.getValue());
}
BigNumber operator*(long n1, const BigNumber& n2)
{
    return BigNumber(n1 * n2.getValue());
}
BigNumber operator/(long n1, const BigNumber& n2)
{
    return BigNumber(n1 / n2.getValue());
}
BigNumber operator%(long n1, const BigNumber& n2)
{
    return BigNumber(n1 % n2.getValue());
}

BigNumber operator+(const BigNumber& n1, long n2)
{
    return BigNumber(n1.getValue() + n2);
}
BigNumber operator-(const BigNumber& n1, long n2)
{
    return BigNumber(n1.getValue() - n2);
}
BigNumber operator*(const BigNumber& n1, long n2)
{
    return BigNumber(n1.getValue() * n2);
}
BigNumber operator/(const BigNumber& n1, long n2)
{
    return BigNumber(n1.getValue() / n2);
}
BigNumber operator%(const BigNumber& n1, long n2)
{
    return BigNumber(n1.getValue() % n2);
}

bool operator==(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() == n2.getValue();
}
bool operator!=(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() != n2.getValue();
}
bool operator>(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() > n2.getValue();
}
bool operator<(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() < n2.getValue();
}
bool operator>=(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() >= n2.getValue();
}
bool operator<=(const BigNumber& n1, const BigNumber& n2)
{
    return n1.getValue() <= n2.getValue();
}

std::ostream& operator<<(std::ostream& out, const BigNumber& n)
{
    return out << n.getValue();
}

} //namespace lisp
