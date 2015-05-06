#include <lisp/Environment.hpp>
#include <lisp/types/Object.hpp>
#include <lisp/util/Formatter.hpp>

#include <iostream>
#include <exception>

namespace lisp
{

Environment::Environment():
    d_env(),
    d_defines() {}
Environment::Environment(const std::shared_ptr<Environment>& env):
    d_env(env),
    d_defines() {}

void Environment::define(const std::string& name, const std::shared_ptr<const Object>& obj)
{
    auto result = d_defines.insert(std::make_pair(name, obj));
    if (!result.second)
    {
        std::cerr << "Warning: Redefinition of '" << name << "'" << std::endl;
        result.first->second = obj;
    }
}

std::shared_ptr<const Object> Environment::get(const std::string& name) const
{
    auto search = d_defines.find(name);
    if (search != d_defines.end())
        return search->second;

    if (d_env)
        return d_env->get(name);

    throw std::runtime_error(Fmt() << "Undefined symbol '" << name << "'");

    return nullptr;
}

void Environment::clear()
{
    d_defines.clear();
}

bool Environment::isRelated(const std::shared_ptr<Environment>& env) const
{
    if (!env)
        throw std::runtime_error("Environment is null");
    return env == d_env || (d_env && d_env->isRelated(env));
}

} //namespace lisp
