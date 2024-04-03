#ifndef TRACEROUTE_CLI_FLAGS_HPP
#define TRACEROUTE_CLI_FLAGS_HPP

#include "flag.hpp"

#include <list>
#include <map>
#include <string>
#include <sstream>

namespace traceroute {
namespace cli {

class Flags {
public:
  void Add(Flag const &flag);

  bool HasShortName(std::string const &short_name) const;
  bool HasLongName(std::string const &long_name) const;
  bool HasName(std::string const &name) const;

  Flag const &get_by_short_name(std::string const &short_name) const;
  Flag const &get_by_long_name(std::string const &long_name) const;
  Flag const &get_by_name(std::string const &name) const;

  std::string FormUsage() const;


  friend class DefaultParser;

private:
  std::list<Flag> flags_;

  std::map<std::string, Flag *> short_flags_;
  std::map<std::string, Flag *> long_flags_;
  std::list<Flag *> required_flags_;

  inline static const std::string kUsagePrefix = "  ";
};

} // namespace cli
} // namespace traceroute

#endif // TRACEROUTE_CLI_FLAGS_HPP