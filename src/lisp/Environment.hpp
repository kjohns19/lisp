#ifndef INCLUDED_LISP_ENVIRONMENT_HPP
#define INCLUDED_LISP_ENVIRONMENT_HPP

#include <map>
#include <memory>
#include <string>

namespace lisp
{

class Object;

class Environment
{
public:
    Environment();
    Environment(const std::shared_ptr<Environment>& env);

    void define(const std::string& name, const std::shared_ptr<const Object>& obj);
    std::shared_ptr<const Object> get(const std::string& name) const;

    void clear();

    bool isRelated(const std::shared_ptr<Environment>& env) const;
private:
    std::shared_ptr<Environment> d_env;
    std::map<std::string, std::shared_ptr<const Object> > d_defines;
};

} //namespace lisp

#endif //INCLUDED_LISP_ENVIRONMENT_HPP
