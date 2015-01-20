#include <lisp/Object.hpp>
#include <lisp/Environment.hpp>

namespace lisp
{

Object::~Object() {}

std::shared_ptr<const Object> Object::evaluate() const
{
    return shared_from_this();
}

std::shared_ptr<const Object> Object::bind(const std::shared_ptr<Environment>& env) const
{
    return shared_from_this();
}

std::shared_ptr<const Object> Object::evaluateCompletely() const
{
    if (isEvaluated())
        return shared_from_this();

    auto val = evaluate();
    while(!val->isEvaluated())
        val = val->evaluate();

    return val;
}

const char* Object::typeName(Type type)
{
    switch(type)
    {
        case LIST:
            return "list";
        case NUMBER:
            return "number";
        case FUNCTION:
            return "function";
        case SYMBOL:
            return "symbol";
        case STRING:
            return "string";
        default:
            return "unknown";
    }
}

} //namespace lisp
