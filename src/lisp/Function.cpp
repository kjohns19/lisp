#include <lisp/Function.hpp>
#include <lisp/List.hpp>
#include <lisp/Environment.hpp>
#include <iostream>

namespace lisp
{

Function::Function(const Func& func):
    d_func(func),
    d_args(),
    d_body(),
    d_builtin(true) {}

Function::Function(const std::vector<std::string>& args,
         const std::shared_ptr<const Object>& body):
    d_func(),
    d_args(args),
    d_body(body),
    d_builtin(false) {}

std::shared_ptr<const Object> Function::evaluate() const
{
    std::cerr << "Cannot evaluate function" << std::endl;
    return nullptr;
}

Object::Type Function::getType() const
{
    return Object::FUNCTION;
}

bool Function::isEvaluated() const
{
    return true;
}

std::shared_ptr<const Object> Function::call(
        const std::shared_ptr<const List>& args,
        const std::shared_ptr<Environment>& env) const
{
    //TODO handle currying

    if (d_builtin)
        return d_func(args, env);
    else
    {
        std::vector<std::shared_ptr<const Object> > vec;
        args->toVector(vec);

        if (vec.size() != d_args.size())
        {
            std::cerr << "Wrong number of arguments ("
                      << vec.size() << " for "
                      << d_args.size() << ")" << std::endl;
            return nullptr;
        }

        auto newenv = std::make_shared<Environment>(env);

        for(size_t i = 0; i < vec.size(); i++)
            newenv->define(d_args[i], vec[i]);

        return d_body->bind(newenv);
    }
}

} //namespace lisp
