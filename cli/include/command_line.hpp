#ifndef TRACEROUTE_CLI_COMMAND_LINE_HPP
#define TRACEROUTE_CLI_COMMAND_LINE_HPP

#include "arguments.hpp"
#include "flags.hpp"

#include <string>
#include <vector>

namespace traceroute {
namespace cli {

class CommandLine {
public:
  Flag const &get_by_short_name(std::string const &short_name) const;
  Flag const &get_by_long_name(std::string const &long_name) const;
  Flag const &get_by_name(std::string const &name) const;

  std::string const &invoke_cmd() const;
  std::vector<std::string> arguments() const;


  friend class DefaultParser;
  
private:
  std::string invoke_cmd_;
  Arguments args_;
  Flags flags_;
};

}
}

#endif // TRACEROUTE_CLI_COMMAND_LINE_HPP