#include <lisp/types/Symbol.hpp>
#include <lisp/Environment.hpp>
#include <exception>

namespace lisp
{

constexpr const char* Symbol::type;

Symbol::Symbol(const std::string& name, const std::shared_ptr<Environment>& env):
    d_name(name),
    d_env(env) {}

const std::string& Symbol::getName() const
{
    return d_name;
}

std::shared_ptr<const Object> Symbol::evaluate() const
{
    if (auto env = d_env.lock())
        return env->get(d_name);
    throw std::runtime_error("Couldn't get environment");
}

std::shared_ptr<const Object> Symbol::bind(const std::shared_ptr<Environment>& env) const
{
    return std::make_shared<Symbol>(d_name, env);
}

const char* Symbol::getType() const
{
    return Symbol::type;
}

bool Symbol::isEvaluated() const
{
    return false;
}

void Symbol::print(std::ostream& out) const
{
    out << d_name;
}

} //namespace lisp
