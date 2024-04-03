#ifndef TRACEROUTE_CLI_PARSER_HPP
#define TRACEROUTE_CLI_PARSER_HPP

#include "arguments.hpp"
#include "command_line.hpp"
#include "flags.hpp"

#include <map>
#include <string>

namespace traceroute {
namespace cli {

class Parser {
public:
  virtual CommandLine Parse(Arguments const &args, Flags const &flags) = 0;
  virtual ~Parser() {}
};

}
}

#endif // TRACEROUTE_CLI_PARSER_HPP