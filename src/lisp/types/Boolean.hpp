#ifndef INCLUDED_LISP_BOOLEAN_HPP
#define INCLUDED_LISP_BOOLEAN_HPP

#include <lisp/types/Object.hpp>

namespace lisp
{

class Boolean : public Object
{
public:
    static constexpr const char* type = "boolean";

    Boolean(bool value);

    virtual const char* getType() const;

    virtual bool isEvaluated() const;

    virtual bool isTrue() const;

    bool getValue() const;

    virtual void print(std::ostream& out) const;
private:
    bool d_value;
};

} //namespace lisp

#endif //INCLUDED_LISP_BOOLEAN_HPP
