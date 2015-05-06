#ifndef INCLUDED_LISP_STRING_HPP
#define INCLUDED_LISP_STRING_HPP

#include <lisp/types/Object.hpp>
#include <string>

namespace lisp
{

class String : public Object
{
public:
    static constexpr const char* type = "string";

    String(const std::string& value);

    const std::string& getValue() const;

    virtual const char* getType() const;

    virtual bool isEvaluated() const;

    virtual void print(std::ostream& out) const;
private:
    std::string d_value;
};

String operator+(const String& s1, const String& s2);

bool operator==(const String& s1, const String& s2);
bool operator!=(const String& s1, const String& s2);
bool operator>=(const String& s1, const String& s2);
bool operator<=(const String& s1, const String& s2);
bool operator>(const String& s1, const String& s2);
bool operator<(const String& s1, const String& s2);

} //namespace lisp

#endif //INCLUDED_LISP_STRING_HPP
