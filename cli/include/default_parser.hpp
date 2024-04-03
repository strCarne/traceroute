#ifndef TRACEROUTE_CLI_DEFAULT_PARSER_HPP
#define TRACEROUTE_CLI_DEFAULT_PARSER_HPP

#include "parser.hpp"

#include <string>
#include <vector>

namespace traceroute {
namespace cli {

class DefaultParser : public Parser {
public:
  CommandLine Parse(Arguments const &args, Flags const &flags) override;
};

} // namespace cli
} // namespace traceroute

#endif // TRACEROUTE_CLI_DEFAULT_PARSER_HPP