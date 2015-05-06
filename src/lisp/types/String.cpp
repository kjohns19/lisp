#include <lisp/types/String.hpp>

namespace lisp
{

constexpr const char* String::type;

String::String(const std::string& value):
    d_value(value) {}

const std::string& String::getValue() const
{
    return d_value;
}

const char* String::getType() const
{
    return String::type;
}

bool String::isEvaluated() const
{
    return true;
}

void String::print(std::ostream& out) const
{
    out << d_value;
}

String operator+(const String& s1, const String& s2)
{
    return String(s1.getValue() + s2.getValue());
}

bool operator==(const String& s1, const String& s2)
{
    return s1.getValue() == s2.getValue();
}
bool operator!=(const String& s1, const String& s2)
{
    return s1.getValue() != s2.getValue();
}
bool operator>=(const String& s1, const String& s2)
{
    return s1.getValue() >= s2.getValue();
}
bool operator<=(const String& s1, const String& s2)
{
    return s1.getValue() <= s2.getValue();
}
bool operator>(const String& s1, const String& s2)
{
    return s1.getValue() > s2.getValue();
}
bool operator<(const String& s1, const String& s2)
{
    return s1.getValue() < s2.getValue();
}

} //namespace lisp
