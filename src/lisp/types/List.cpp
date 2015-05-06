#include <lisp/types/List.hpp>
#include <lisp/Environment.hpp>
#include <lisp/types/Function.hpp>
#include <lisp/types/Object.hpp>

#include <iostream>

namespace lisp
{

constexpr const char* List::type;

const std::shared_ptr<const List> List::Null = std::make_shared<List>(nullptr, nullptr, nullptr, true);

List::List(const std::shared_ptr<const Object>& head,
           const std::shared_ptr<const List>& tail,
           const std::shared_ptr<Environment>& env,
           bool evaluated):
    d_head(head),
    d_tail(tail),
    d_env(env),
    d_cached(),
    d_evaluated(evaluated) {}

const std::shared_ptr<const Object> List::getHead() const
{
    if (isNull())
        throw std::runtime_error("Cannot get head of null");
    return d_head->bind(d_env);
}
const std::shared_ptr<const List> List::getTail() const
{
    if (isNull())
        throw std::runtime_error("Cannot get tail of null");
    return toType<List>(d_tail->bind(d_env));
}

std::shared_ptr<const Object> List::evaluate() const
{
    if (isNull())
        return Null;

    if (!d_cached)
    {
        auto func = toType<Function>(getHead()->evaluateCompletely());

        d_cached = func->call(getTail()->toVector(), d_env);
    }
    return d_cached;
}

std::shared_ptr<const Object> List::bind(const std::shared_ptr<Environment>& env) const
{
    if (!isNull())
    {
        if (env->isRelated(d_env))
            return std::make_shared<List>(d_head, d_tail, env, d_evaluated);
    }
    return shared_from_this();
}

const char* List::getType() const
{
    return List::type;
}

bool List::isEvaluated() const
{
    return d_evaluated;
}

bool List::isNull() const
{
    return !d_head && !d_tail;
}

bool List::isTrue() const
{
    return !isNull();
}

size_t List::length() const
{
    if (isNull())
        return 0;
    return 1 + d_tail->length();
}

std::shared_ptr<const List> List::append(const std::shared_ptr<const List>& list) const
{
    if (isNull())
        return list;
    return std::make_shared<const List>(getHead(), getTail()->append(list), d_env);
}

std::vector<std::shared_ptr<const Object> > List::toVector() const
{
    std::vector<std::shared_ptr<const Object> > vec;
    toVector(vec);
    return vec;
}

void List::toVector(std::vector<std::shared_ptr<const Object> >& vec) const
{
    if (!isNull())
    {
        vec.push_back(getHead());
        auto list = getTail();
        while(!list->isNull())
        {
            vec.push_back(list->getHead());
            list = list->getTail();
        }
    }
}

void List::print(std::ostream& out) const
{
    out << "(";
    if (!isNull())
    {
        d_head->print(out);
        out << " . ";
        d_tail->print(out);
    }
    out << ")";
}


} //namespace lisp
