#ifndef INCLUDED_LISP_SYMBOL_HPP
#define INCLUDED_LISP_SYMBOL_HPP

#include <lisp/types/Object.hpp>
#include <string>
#include <memory>

namespace lisp
{

class Environment;

class Symbol : public Object
{
public:
    static constexpr const char* type = "symbol";

    Symbol(const std::string& name, const std::shared_ptr<Environment>& env);

    const std::string& getName() const;

    virtual std::shared_ptr<const Object> evaluate() const;

    virtual std::shared_ptr<const Object> bind(const std::shared_ptr<Environment>& env) const;

    virtual const char* getType() const;


    virtual bool isEvaluated() const;

    virtual void print(std::ostream& out) const;
private:
    std::string d_name;
    std::weak_ptr<Environment> d_env;
};

} //namespace lisp

#endif //INCLUDED_LISP_SYMBOL_HPP
