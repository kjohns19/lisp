#include <lisp/List.hpp>
#include <lisp/Environment.hpp>
#include <lisp/Function.hpp>

#include <iostream>

namespace lisp
{

const std::shared_ptr<List> List::Null = std::make_shared<List>(nullptr, nullptr, nullptr, true);

List::List(const std::shared_ptr<const Object>& head,
           const std::shared_ptr<const Object>& tail,
           const std::shared_ptr<Environment>& env,
           bool evaluated):
    d_head(head),
    d_tail(tail),
    d_env(env),
    d_evaluated(evaluated) {}

const std::shared_ptr<const Object> List::getHead() const
{
    if (isNull())
    {
        std::cerr << "Cannot get head of null" << std::endl;
        return nullptr;
    }
    return d_head->bind(d_env);
}
const std::shared_ptr<const Object> List::getTail() const
{
    if (isNull())
    {
        std::cerr << "Cannot get tail of null" << std::endl;
        return nullptr;
    }
    return d_tail->bind(d_env);
}

std::shared_ptr<const Object> List::evaluate() const
{
    if (isNull())
        return Null;

    auto head = getHead()->evaluateCompletely();
    
    auto func = std::dynamic_pointer_cast<const Function>(head);
    if (!func)
    {
        std::cerr << "Expected function, got "
                  << Object::typeName(head->getType()) << std::endl;
        return nullptr;
    }
    auto tail = std::dynamic_pointer_cast<const List>(getTail());
    if (!tail)
    {
        std::cerr << "Tail isn't list" << std::endl;
        return nullptr;
    }

    return func->call(tail, d_env);
}

std::shared_ptr<const Object> List::bind(const std::shared_ptr<Environment>& env) const
{
    if (env->isRelated(d_env))
        return std::make_shared<List>(d_head, d_tail, env, d_evaluated);
    return shared_from_this();
}

Object::Type List::getType() const
{
    return Object::LIST;
}

bool List::isEvaluated() const
{
    return d_evaluated;
}

bool List::isNull() const
{
    if (this == List::Null.get())
        return true;
    if (!d_head && !d_tail)
        std::cerr << "Shouldn't be null but is!" << std::endl;
    return false;
}

void List::toVector(std::vector<std::shared_ptr<const Object> >& vec) const
{
    if (!isNull())
    {
        vec.push_back(getHead());
        auto tail = std::dynamic_pointer_cast<const List>(getTail());
        if (tail)
            tail->toVector(vec);
        else
            std::cout << "Tail isn't list" << std::endl;
    }
}


} //namespace lisp
