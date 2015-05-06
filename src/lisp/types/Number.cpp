#include <lisp/types/Number.hpp>

namespace lisp
{

constexpr const char* Number::type;

Number::Number(const Value& value):
    d_value(value) {}

Number::Number(Value&& value):
    d_value(std::move(value)) {}

Number::Number(Number&& number):
    d_value(std::move(number.d_value)) {}

const char* Number::getType() const
{
    return Number::type;
}

bool Number::isEvaluated() const
{
    return true;
}

const Number::Value& Number::getValue() const
{
    return d_value;
}

void Number::print(std::ostream& out) const
{
    out << d_value;
}

Number operator+(const Number& n1, const Number& n2)
{
    return Number(n1.getValue() + n2.getValue());
}
Number operator-(const Number& n1, const Number& n2)
{
    return Number(n1.getValue() - n2.getValue());
}
Number operator*(const Number& n1, const Number& n2)
{
    return Number(n1.getValue() * n2.getValue());
}
Number operator/(const Number& n1, const Number& n2)
{
    return Number(n1.getValue() / n2.getValue());
}
Number operator%(const Number& n1, const Number& n2)
{
    return Number(n1.getValue() % n2.getValue());
}

bool operator==(const Number& n1, const Number& n2)
{
    return n1.getValue() == n2.getValue();
}
bool operator!=(const Number& n1, const Number& n2)
{
    return n1.getValue() != n2.getValue();
}
bool operator>(const Number& n1, const Number& n2)
{
    return n1.getValue() > n2.getValue();
}
bool operator<(const Number& n1, const Number& n2)
{
    return n1.getValue() < n2.getValue();
}
bool operator>=(const Number& n1, const Number& n2)
{
    return n1.getValue() >= n2.getValue();
}
bool operator<=(const Number& n1, const Number& n2)
{
    return n1.getValue() <= n2.getValue();
}

} //namespace lisp
