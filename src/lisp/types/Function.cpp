#include <lisp/types/Function.hpp>
#include <lisp/types/List.hpp>
#include <lisp/Environment.hpp>
#include <iostream>
#include <sstream>

namespace lisp
{

constexpr const char* Function::type;

Function::Function(const std::vector<std::string>& args, const Func& func):
    d_func(func),
    d_args(args),
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

const char* Function::getType() const
{
    return Function::type;
}

bool Function::isEvaluated() const
{
    return true;
}

std::shared_ptr<const Object> Function::call(
        const std::vector<std::shared_ptr<const Object> >& args,
        const std::shared_ptr<Environment>& env) const
{
    size_t len = args.size();
    if (len == d_args.size())
        return internalCall(args, env);
    else if (len < d_args.size())
    {
        std::vector<std::string> newNames;
        for(size_t i = len; i < d_args.size(); i++)
            newNames.push_back(d_args[i]);

        auto newargs = args;
        size_t size = newargs.size();
        
        return std::make_shared<const Function>(newNames,
            [this, newargs, size]
                (const std::vector<std::shared_ptr<const Object> >& args,
                 const std::shared_ptr<Environment>& env) mutable {
            newargs.resize(size);
            newargs.insert(newargs.end(), args.begin(), args.end());
            return call(newargs, env);
        });
    }
    else
    {
        auto result = internalCall(args, env)->evaluateCompletely();

        auto func = toType<Function>(result, false);
        if (func)
        {
            std::vector<std::shared_ptr<const Object> > newargs(
                args.begin()+d_args.size(), args.end());

            return func->call(newargs, env);
        }
        else
        {
            std::stringstream ss;
            ss << "Wrong number of arguments for ";
            print(ss);
            ss << " (" << len << " for " << d_args.size();
            throw std::runtime_error(ss.str());
        }
    }
}

std::shared_ptr<const Object> Function::internalCall(
        const std::vector<std::shared_ptr<const Object> >& args,
        const std::shared_ptr<Environment>& env) const
{

    if (d_builtin)
        return d_func(args, env);
    else
    {
        auto newenv = std::make_shared<Environment>(env);

        for(size_t i = 0; i < d_args.size(); i++)
            newenv->define(d_args[i], args[i]);

        return d_body->bind(newenv);
    }
}

void Function::print(std::ostream& out) const
{
    out << "<lambda";
    for(auto& arg: d_args)
        out << " " << arg;
    out << ">";
}

} //namespace lisp
