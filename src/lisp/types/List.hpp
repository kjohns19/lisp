#ifndef INCLUDED_LISP_LIST_HPP
#define INCLUDED_LISP_LIST_HPP

#include <lisp/types/Object.hpp>

#include <memory>
#include <vector>

namespace lisp
{

class List : public Object
{
public:
    static constexpr const char* type = "list";

    List(const std::shared_ptr<const Object>& head,
         const std::shared_ptr<const List>& tail,
         const std::shared_ptr<Environment>& env,
         bool evaluated = false);

    const std::shared_ptr<const Object> getHead() const;
    const std::shared_ptr<const List> getTail() const;

    virtual std::shared_ptr<const Object> evaluate() const;

    virtual std::shared_ptr<const Object> bind(const std::shared_ptr<Environment>& env) const;

    virtual const char* getType() const;

    virtual bool isEvaluated() const;

    virtual bool isNull() const;

    virtual bool isTrue() const;

    size_t length() const;

    std::shared_ptr<const List> append(const std::shared_ptr<const List>& list) const;

    std::vector<std::shared_ptr<const Object> > toVector() const;
    void toVector(std::vector<std::shared_ptr<const Object> >& vec) const;

    virtual void print(std::ostream& out) const;

    static const std::shared_ptr<const List> Null;
private:
    std::shared_ptr<const Object> d_head;
    std::shared_ptr<const List> d_tail;
    std::shared_ptr<Environment> d_env;
    mutable std::shared_ptr<const Object> d_cached;
    bool d_evaluated;
};

} //namespace lisp

#endif //INCLUDED_LISP_LIST_HPP
