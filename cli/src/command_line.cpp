#include "command_line.hpp"

namespace traceroute {
namespace cli {

Flag const &
CommandLine::get_by_short_name(std::string const &short_name) const {
  if (flags_.HasShortName(short_name)) {
    return flags_.get_by_short_name(short_name);
  }
  throw new std::invalid_argument("err: no flags with short name " +
                                  short_name);
}
Flag const &CommandLine::get_by_long_name(std::string const &long_name) const {
  if (flags_.HasLongName(long_name)) {
    return flags_.get_by_long_name(long_name);
  }
  throw new std::invalid_argument("err: no flags with long name " + long_name);
}

Flag const &CommandLine::get_by_name(std::string const &name) const {
  if (flags_.HasName(name)) {
    return flags_.get_by_name(name);
  }
  throw new std::invalid_argument("err: no flags with short or long name " +
                                  name);
}

std::string const &CommandLine::invoke_cmd() const { return invoke_cmd_; }

std::vector<std::string> CommandLine::arguments() const { return args_.args_; }

} // namespace cli
} // namespace traceroute