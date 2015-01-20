#ifndef INCLUDED_LIST_HPP
#define INCLUDED_LIST_HPP

#include <lisp/Object.hpp>

#include <memory>
#include <vector>

namespace lisp
{

class List : public Object
{
public:
    List(const std::shared_ptr<const Object>& head,
         const std::shared_ptr<const Object>& tail,
         const std::shared_ptr<Environment>& env,
         bool evaluated = false);

    const std::shared_ptr<const Object> getHead() const;
    const std::shared_ptr<const Object> getTail() const;

    virtual std::shared_ptr<const Object> evaluate() const;

    virtual std::shared_ptr<const Object> bind(const std::shared_ptr<Environment>& env) const;

    virtual Object::Type getType() const;

    virtual bool isEvaluated() const;

    virtual bool isNull() const;

    void toVector(std::vector<std::shared_ptr<const Object> >& vec) const;

    static const std::shared_ptr<List> Null;

private:
    std::shared_ptr<const Object> d_head;
    std::shared_ptr<const Object> d_tail;
    std::shared_ptr<Environment> d_env;
    bool d_evaluated;
};

} //namespace lisp

#endif //INCLUDED_LIST_HPP
