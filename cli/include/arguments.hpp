#ifndef TRACEROUTE_CLI_ARGUMENTS_HPP
#define TRACEROUTE_CLI_ARGUMENTS_HPP

#include <string>
#include <vector>

namespace traceroute {
namespace cli {

class Arguments {
public:
  Arguments(int argc, char **argv);
  Arguments() {}

  friend class DefaultParser;
  friend class CommandLine;

private:
  std::vector<std::string> args_;
};

} // namespace cli
} // namespace traceroute

#endif // TRACEROUTE_CLI_ARGUMENTS_HPP