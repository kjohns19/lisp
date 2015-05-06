#include <lisp/Parser.hpp>
#include <lisp/types/Object.hpp>
#include <lisp/types/Symbol.hpp>
#include <lisp/Environment.hpp>
#include <lisp/types/Function.hpp>
#include <lisp/types/List.hpp>
#include <lisp/types/Boolean.hpp>
#include <lisp/types/Number.hpp>
#include <lisp/types/String.hpp>
#include <lisp/util/Formatter.hpp>

#include <iostream>
#include <exception>
#include <fstream>

using namespace lisp;

typedef std::vector<std::shared_ptr<const Object> > Vec;
typedef std::shared_ptr<Environment> EnvPtr;

void define(const EnvPtr& env,
            const std::string& name,
            const std::initializer_list<std::string>& args,
            const Function::Func& func);

void printObject(const std::shared_ptr<const Object>& obj, std::ostream& out);

int main()
{
    auto env = std::make_shared<Environment>();

    define(env, "define", {"name", "value"}, [](const Vec& args, const EnvPtr& env) {
        auto symbol = toType<Symbol>(args[0]);

        env->define(symbol->getName(), args[1]);

        return List::Null;
    });

    #define NUMBER_FUNC(op, type) \
        define(env, #op, {"a", "b"}, [](const Vec& args, const EnvPtr& env) { \
            auto val1 = toType<Number>(args[0]->evaluateCompletely()); \
            auto val2 = toType<Number>(args[1]->evaluateCompletely()); \
            return std::make_shared<const type>((*val1.get()) op (*val2.get())); \
        })

    NUMBER_FUNC(+, Number);
    NUMBER_FUNC(-, Number);
    NUMBER_FUNC(*, Number);
    NUMBER_FUNC(/, Number);
    NUMBER_FUNC(%, Number);

    NUMBER_FUNC(==, Boolean);
    NUMBER_FUNC(!=, Boolean);
    NUMBER_FUNC(>,  Boolean);
    NUMBER_FUNC(<,  Boolean);
    NUMBER_FUNC(>=, Boolean);
    NUMBER_FUNC(<=, Boolean);

    #undef NUMBER_FUNC

    #define BOOL_FUNC(name, op, rev) \
        define(env, #name, {"a", "b"}, [](const Vec& args, const EnvPtr& env) { \
            bool val1 = args[0]->evaluateCompletely()->isTrue(); \
            if ((val1 op true) == (val1 op false)) \
                return std::make_shared<Boolean>(rev(val1 op true)); \
            bool val2 = args[1]->evaluateCompletely()->isTrue(); \
            return std::make_shared<Boolean>(rev(val1 op val2)); \
        })

    BOOL_FUNC(or, ||, !!);
    BOOL_FUNC(and, &&, !!);
    BOOL_FUNC(xor, !=, !!);

    BOOL_FUNC(nor, ||, !);
    BOOL_FUNC(nand, &&, !);
    BOOL_FUNC(xnor, !=, !);

    #undef BOOL_FUNC

    #define TYPE_FUNC(type, name) \
    define(env, name, {"value"}, [](const Vec& args, const EnvPtr& env) { \
        auto cast = toType<type>(args[0]->evaluateCompletely(), false); \
        return std::make_shared<Boolean>(cast ? true : false); \
    })

    TYPE_FUNC(List,     "list?");
    TYPE_FUNC(Number,   "number?");
    TYPE_FUNC(String,   "string?");
    TYPE_FUNC(Function, "function?");
    TYPE_FUNC(Boolean,  "boolean?");

    #undef TYPE_FUNC

    define(env, "not", {"value"}, [](const Vec& args, const EnvPtr& env) {
        return std::make_shared<Boolean>(!args[0]->evaluateCompletely()->isTrue());
    });

    define(env, "cons", {"head", "lst"}, [](const Vec& args, const EnvPtr& env) {
        return std::make_shared<const List>(args[0], toType<List>(args[1]), env, true);
    });

    define(env, "car", {"lst"}, [](const Vec& args, const EnvPtr& env) {
        auto list = toType<List>(args[0]->evaluateCompletely());
        return list->getHead();
    });

    define(env, "cdr", {"lst"}, [](const Vec& args, const EnvPtr& env) {
        auto list = toType<List>(args[0]->evaluateCompletely());
        return list->getTail();
    });

    define(env, "if", {"cond", "true", "false"}, [](const Vec& args, const EnvPtr& env) {
        auto cond = args[0]->evaluateCompletely();
        if (cond->isTrue())
            return args[1];
        else
            return args[2];
    });

    define(env, "null?", {"value"}, [](const Vec& args, const EnvPtr& env) {
        auto arg = args[0]->evaluateCompletely();
        auto list = toType<List>(arg, false);
        return std::make_shared<Boolean>(list && list->isNull());
    });
    env->define("null", List::Null);

    define(env, "lambda", {"args", "value"}, [](const Vec& args, const EnvPtr& env) {
        auto argList = toType<List>(args[0])->toVector();
        std::vector<std::string> argNames;
        for(auto& arg: argList)
        {
            auto sym = toType<Symbol>(arg);
            argNames.push_back(sym->getName());
        }

        return std::make_shared<Function>(argNames, args[1]);
    });

    define(env, "let", {"args", "value"}, [](const Vec& args, const EnvPtr& env) {
        auto newenv = std::make_shared<Environment>(env);

        auto letList = toType<List>(args[0])->toVector();
        for(auto& arg: letList)
        {
            auto list = toType<List>(arg)->toVector();
            if (list.size() != 2)
                throw std::runtime_error("Let list must contains lists of 2 elements");
            auto symbol = toType<Symbol>(list[0]);
            newenv->define(symbol->getName(), list[1]);
        }

        return args[1]->bind(newenv);
    });

    define(env, "comment", {"comment"}, [](const Vec& args, const EnvPtr& env) {
        return List::Null;
    });

    std::shared_ptr<const Object> obj;
    if (1)
    {
        std::ifstream in("functions.lisp");
        while(obj = parse(in, env))
            obj->evaluateCompletely();
    }

    while(1)
    {
        try
        {
            obj = parse(std::cin, env);
            if (obj)
            {
                //obj->print(std::cout);
                printObject(obj, std::cout);
                std::cout << std::endl;
            }
            else
                break;
        }
        catch (std::runtime_error& err)
        {
            std::cerr << "Error: " << err.what() << std::endl;
        }
    }

    env->clear();

    return 0;
}

void define(const EnvPtr& env,
            const std::string& name,
            const std::initializer_list<std::string>& args,
            const Function::Func& func)
{
    std::vector<std::string> vec_args(args);
    env->define(name, std::make_shared<const Function>(vec_args, func));
}

void printObject(const std::shared_ptr<const Object>& obj, std::ostream& out)
{
    auto evaluated = obj->evaluateCompletely();
    auto list = toType<List>(evaluated, false);

    if (list)
    {
        out << "(";
        if (!list->isNull())
            while(1)
            {
                printObject(list->getHead(), out);
                list = toType<List>(list->getTail()->evaluateCompletely());
                if (list->isNull())
                    break;
                else
                    out << " ";
            }
        out << ")";
    }
    else
        evaluated->print(out);
    out << std::flush;
}
