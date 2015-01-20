#ifndef INCLUDED_PARSER_HPP
#define INCLUDED_PARSER_HPP

#include <memory>
#include <vector>
#include <string>
#include <istream>

namespace lisp
{

class Object;
class Environment;

std::vector<std::shared_ptr<Object> > parse(
        const std::string& input,
        const std::shared_ptr<Environment>& env);

std::vector<std::shared_ptr<Object> > parse(
        std::istream& stream,
        const std::shared_ptr<Environment>& env);

} //namespace lisp

#endif //INCLUDED_PARSER_HPP
