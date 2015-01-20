#include <lisp/Environment.hpp>
#include <lisp/Object.hpp>

#include <iostream>

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
    d_defines[name] = obj;
}

std::shared_ptr<const Object> Environment::get(const std::string& name) const
{
    auto search = d_defines.find(name);
    if (search != d_defines.end())
        return search->second;

    if (d_env)
        return d_env->get(name);

    //TODO Throw exception? idk
    std::cerr << "ERROR: Undefined symbol '" << name << "'" << std::endl;

    return nullptr;
}

bool Environment::isRelated(const std::shared_ptr<Environment>& env) const
{
    return env == d_env || (d_env && d_env->isRelated(env));
}

} //namespace lisp
