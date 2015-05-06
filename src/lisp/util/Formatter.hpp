#ifndef INCLUDED_LISP_FORMATTER_HPP
#define INCLUDED_LISP_FORMATTER_HPP

#include <sstream>

namespace lisp
{

class Fmt
{
public:
    Fmt():
        d_message() {}

    template<typename T>
    Fmt& operator<<(const T& obj)
    {
        d_message << obj;
        return *this;
    }

    operator std::string() const
    {
        return d_message.str();
    }
private:
    std::stringstream d_message;
};

} //namespace lisp

#endif //INCLUDED_LISP_FORMATTER_HPP
