#ifndef INCLUDED_LISP_NUMBER_HPP
#define INCLUDED_LISP_NUMBER_HPP

#include <lisp/types/Object.hpp>
#include <lisp/util/BigNumber.hpp>

namespace lisp
{

class Number : public Object
{
public:
    typedef BigNumber Value;

    static constexpr const char* type = "number";

    Number(const Value& value);
    Number(Value&& value);
    Number(Number&& number);

    virtual const char* getType() const;

    virtual bool isEvaluated() const;

    const Value& getValue() const;

    virtual void print(std::ostream& out) const;
private:
    Value d_value;
};

Number operator+(const Number& n1, const Number& n2);
Number operator-(const Number& n1, const Number& n2);
Number operator*(const Number& n1, const Number& n2);
Number operator/(const Number& n1, const Number& n2);
Number operator%(const Number& n1, const Number& n2);

bool operator==(const Number& n1, const Number& n2);
bool operator!=(const Number& n1, const Number& n2);
bool operator>(const Number& n1, const Number& n2);
bool operator<(const Number& n1, const Number& n2);
bool operator>=(const Number& n1, const Number& n2);
bool operator<=(const Number& n1, const Number& n2);

} //namespace lisp

#endif //INCLUDED_LISP_NUMBER_HPP
