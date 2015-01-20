#include <lisp/Parser.hpp>
#include <lisp/Object.hpp>
#include <lisp/List.hpp>
#include <lisp/Environment.hpp>

#include <sstream>
#include <iostream>

typedef std::shared_ptr<lisp::Environment> Env;


static std::string nextToken(std::istream& stream);

static std::shared_ptr<lisp::Object> nextObject(std::istream& stream,
                                          const Env& env,
                                          bool list = false);

static std::shared_ptr<lisp::Object> getObject(const std::string& str, const Env& env);


namespace lisp
{

std::vector<std::shared_ptr<Object> > parse(const std::string& input, const Env& env)
{
    std::stringstream stream;
    stream << input;
    return parse(stream, env);
}

std::vector<std::shared_ptr<Object> > parse(std::istream& stream, const Env& env)
{
    std::vector<std::shared_ptr<Object> > vec;

    while(1)
    {
        auto obj = nextObject(stream, env);
        if (obj)
            vec.push_back(obj);
        else
            break;
    }

    return vec;
}

} //namespace lisp

std::string nextToken(std::istream& stream)
{
    return "";
}

std::shared_ptr<lisp::Object> nextObject(std::istream& stream, const Env& env, bool list)
{
    std::string token = nextToken(stream);

    if (token.empty())
    {
        if (list)
        {
            //TODO Error
            std::cerr << "No matching ')' found" << std::endl;
        }
        return nullptr;
    }

    if (token == "(")
        return nextObject(stream, env, true);
    else if (token == ")")
    {
        if (list)
            return lisp::List::Null;

        //TODO Error
        std::cerr << "Unexpected ')'" << std::endl;
        return nullptr;
    }

    auto obj = getObject(token, env);

    if (list)
    {
        auto tail = nextObject(stream, env, true);
        return std::make_shared<lisp::List>(obj, tail, env);
    }

    return obj;
}

std::shared_ptr<lisp::Object> getObject(const std::string& str, const Env& env)
{
    return nullptr;
}
