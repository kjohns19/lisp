#ifndef INCLUDED_LISP_OBJECT
#define INCLUDED_LISP_OBJECT

#include <lisp/util/Formatter.hpp>

#include <memory>
#include <iostream>
#include <exception>


namespace lisp
{

class Environment;

class Object : public std::enable_shared_from_this<Object>
{
public:
    virtual ~Object();

    virtual std::shared_ptr<const Object> evaluate() const;

    std::shared_ptr<const Object> evaluateCompletely() const;

    virtual std::shared_ptr<const Object> bind(const std::shared_ptr<Environment>& env) const;

    virtual const char* getType() const = 0;

    virtual bool isEvaluated() const = 0;

    virtual bool isTrue() const;

    virtual void print(std::ostream& out) const = 0;
};

template<typename T>
std::shared_ptr<const T> toType(const std::shared_ptr<const Object>& val, bool fail = true)
{
    auto result = std::dynamic_pointer_cast<const T>(val);
    if (result)
        return result;
    if (fail)
        throw std::runtime_error(Fmt() << "Expected " << T::type << ", got " << val->getType());
    return nullptr;
}

} //namespace lisp

#endif //INCLUDED_LISP_OBJECT
