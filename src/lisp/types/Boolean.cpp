#include <lisp/types/Boolean.hpp>

namespace lisp
{

constexpr const char* Boolean::type;

Boolean::Boolean(bool value):
    d_value(value) {}

const char* Boolean::getType() const
{
    return Boolean::type;
}

bool Boolean::isEvaluated() const
{
    return true;
}

bool Boolean::getValue() const
{
    return d_value;
}

bool Boolean::isTrue() const
{
    return d_value;
}

void Boolean::print(std::ostream& out) const
{
    out << (d_value ? "#t" : "#f");
}

} //namespace lisp
