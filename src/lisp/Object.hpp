#ifndef INCLUDED_LISP_OBJECT
#define INCLUDED_LISP_OBJECT

#include <memory>

namespace lisp
{

class Environment;

class Object : public std::enable_shared_from_this<Object>
{
public:
    enum Type { LIST, NUMBER, FUNCTION, SYMBOL, STRING };
    static const char* typeName(Type type);

    virtual ~Object();

    virtual std::shared_ptr<const Object> evaluate() const;

    std::shared_ptr<const Object> evaluateCompletely() const;

    virtual std::shared_ptr<const Object> bind(const std::shared_ptr<Environment>& env) const;

    virtual Type getType() const = 0;

    virtual bool isEvaluated() const = 0;
};

} //namespace lisp

#endif //INCLUDED_LISP_OBJECT
