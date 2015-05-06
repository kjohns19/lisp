#include <lisp/Parser.hpp>
#include <lisp/types/Object.hpp>
#include <lisp/types/List.hpp>
#include <lisp/Environment.hpp>
#include <lisp/types/Number.hpp>
#include <lisp/types/Symbol.hpp>
#include <lisp/types/String.hpp>
#include <lisp/types/Boolean.hpp>
#include <lisp/util/BigNumber.hpp>

#include <algorithm>
#include <sstream>
#include <iostream>
#include <exception>
#include <cctype>

typedef std::shared_ptr<lisp::Environment> Env;


static std::string nextToken(std::istream& stream);

static std::shared_ptr<const lisp::Object> nextObject(std::istream& stream,
                                          const Env& env,
                                          bool list = false,
                                          bool literal = false);

static std::shared_ptr<const lisp::Object> getObject(const std::string& str, const Env& env, bool literal);

static bool isNumber(const std::string& str);

static lisp::BigNumber getNumber(const std::string& str);


namespace lisp
{

std::shared_ptr<const Object> parse(const std::string& input, const Env& env)
{
    std::stringstream stream;
    stream << input;
    return parse(stream, env);
}

std::shared_ptr<const Object> parse(std::istream& stream, const Env& env)
{
    return nextObject(stream, env);
}

} //namespace lisp

std::string nextToken(std::istream& stream)
{
    std::stringstream token;
    char c = ' ';

    if (!stream)
        return "";

    while(stream.get(c))
    {
        if (!std::isspace(c))
            break;
    }

    if (c == ')' || c == '(' || c == '\'')
    {
        token << c;
        return token.str();
    }

    stream.unget();

    while(stream.get(c))
    {
        if (std::isspace(c))
            break;
        else
        {
            if (c == ')' || c == '(')
            {
                stream.unget();
                break;
            }
            token << c;
        }
    }

    return token.str();
}

std::shared_ptr<const lisp::Object> nextObject(std::istream& stream, const Env& env, bool list, bool literal)
{
    std::string token = nextToken(stream);

    if (token == "'")
    {
        literal = true;
        token = nextToken(stream);
    }

    if (token.empty())
    {
        if (list)
            throw std::runtime_error("No matching ')' found");
        return nullptr;
    }

    std::shared_ptr<const lisp::Object> obj;

    if (token == "(")
        obj = nextObject(stream, env, true, literal);
    else if (token == ")")
    {
        if (list)
            return lisp::List::Null;

        throw std::runtime_error("Unexpected ')'");
    }
    else
        obj = getObject(token, env, literal);

    if (list)
    {
        auto tail = lisp::toType<lisp::List>(nextObject(stream, env, true, literal));
        return std::make_shared<const lisp::List>(obj, tail, env, literal);
    }

    return obj;
}

std::shared_ptr<const lisp::Object> getObject(const std::string& str, const Env& env, bool literal)
{
    if (isNumber(str))
        return std::make_shared<const lisp::Number>(getNumber(str));
    if (literal)
        return std::make_shared<const lisp::String>(str);

    if (str == "#t")
        return std::make_shared<lisp::Boolean>(true);
    if (str == "#f")
        return std::make_shared<lisp::Boolean>(false);

    return std::make_shared<const lisp::Symbol>(str, env);
}

bool isNumber(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) {
        return c >= '0' && c <= '9';
    });
}

lisp::BigNumber getNumber(const std::string& str)
{
    lisp::BigNumber num = str[0]-'0';

    for(size_t i = 1; i < str.length(); i++)
        num = num * 10 + (str[i]-'0');

    return num;
}
