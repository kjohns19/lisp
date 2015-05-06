#ifndef INCLUDED_LISP_BIGNUMBER_HPP
#define INCLUDED_LISP_BIGNUMBER_HPP

#include <vector>
#include <ostream>

namespace lisp
{

class BigNumber
{
public:
    BigNumber(long value);

    long getValue() const;
private:
    //std::vector<unsigned> d_value;
    long d_value;
};

BigNumber operator+(const BigNumber& n1, const BigNumber& n2);
BigNumber operator-(const BigNumber& n1, const BigNumber& n2);
BigNumber operator*(const BigNumber& n1, const BigNumber& n2);
BigNumber operator/(const BigNumber& n1, const BigNumber& n2);
BigNumber operator%(const BigNumber& n1, const BigNumber& n2);

BigNumber operator+(long n1, const BigNumber& n2);
BigNumber operator-(long n1, const BigNumber& n2);
BigNumber operator*(long n1, const BigNumber& n2);
BigNumber operator/(long n1, const BigNumber& n2);
BigNumber operator%(long n1, const BigNumber& n2);

BigNumber operator+(const BigNumber& n1, long n2);
BigNumber operator-(const BigNumber& n1, long n2);
BigNumber operator*(const BigNumber& n1, long n2);
BigNumber operator/(const BigNumber& n1, long n2);
BigNumber operator%(const BigNumber& n1, long n2);

bool operator==(const BigNumber& n1, const BigNumber& n2);
bool operator!=(const BigNumber& n1, const BigNumber& n2);
bool operator>(const BigNumber& n1, const BigNumber& n2);
bool operator<(const BigNumber& n1, const BigNumber& n2);
bool operator>=(const BigNumber& n1, const BigNumber& n2);
bool operator<=(const BigNumber& n1, const BigNumber& n2);

std::ostream& operator<<(std::ostream& out, const BigNumber& n);

} //namespace lisp

#endif //INCLUDED_LISP_BIGNUMBER_HPP
