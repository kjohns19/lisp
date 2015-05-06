#ifndef INCLUDED_LISP_FUNCTION_HPP
#define INCLUDED_LISP_FUNCTION_HPP

#include <lisp/types/Object.hpp>

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
            std::shared_ptr<const Object>(const std::vector<std::shared_ptr<const Object> >&,
                                    const std::shared_ptr<Environment>&)> Func;

    static constexpr const char* type = "function";

    Function(const std::vector<std::string>& args, const Func& func);
    Function(const std::vector<std::string>& args,
             const std::shared_ptr<const Object>& body);

    virtual std::shared_ptr<const Object> evaluate() const;

    virtual const char* getType() const;

    virtual bool isEvaluated() const;

    std::shared_ptr<const Object> call(
            const std::vector<std::shared_ptr<const Object> >& args,
            const std::shared_ptr<Environment>& env) const;

    virtual void print(std::ostream& out) const;
private:
    std::shared_ptr<const Object> internalCall(
            const std::vector<std::shared_ptr<const Object> >& args,
            const std::shared_ptr<Environment>& env) const;

    Func d_func;
    std::vector<std::string> d_args;
    std::shared_ptr<const Object> d_body;
    bool d_builtin;
};

} //namespace lisp

#endif //INCLUDED_LISP_FUNCTION_HPP
