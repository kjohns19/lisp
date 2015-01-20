#ifndef INCLUDED_FUNCTION_HPP
#define INCLUDED_FUNCTION_HPP

#include <lisp/Object.hpp>

#include <functional>
#include <string>
#include <vector>

namespace lisp
{

class List;
class Environment;

class Function : public Object
{
public:
    typedef std::function<
            std::shared_ptr<Object>(const std::shared_ptr<const List>&,
                                    const std::shared_ptr<Environment>&)> Func;

    Function(const Func& func);
    Function(const std::vector<std::string>& args,
             const std::shared_ptr<const Object>& body);

    virtual std::shared_ptr<const Object> evaluate() const;

    virtual Type getType() const;

    virtual bool isEvaluated() const;

    std::shared_ptr<const Object> call(const std::shared_ptr<const List>& args,
                                 const std::shared_ptr<Environment>& env) const;
private:
    Func d_func;
    std::vector<std::string> d_args;
    std::shared_ptr<const Object> d_body;
    bool d_builtin;
};

} //namespace lisp

#endif //INCLUDED_FUNCTION_HPP
