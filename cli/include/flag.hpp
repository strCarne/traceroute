#ifndef TRACEROUTE_CLI_FLAG_HPP
#define TRACEROUTE_CLI_FLAG_HPP

#include <string>

namespace traceroute { 
namespace cli {

class Flag {
public:
  Flag(std::string const &short_name, std::string const &long_name,
       bool has_arg, std::string const &usage);

  Flag(std::string const &short_name, std::string const &long_name,
       std::string const &usage);

  Flag(std::string const &name, bool has_arg, std::string const &usage);

  Flag(std::string const &name, std::string const &usage);

  std::string const &short_name() const;
  std::string const &long_name() const;
  std::string const &usage() const;
  std::string const &value() const;
  bool used() const;
  bool required() const;
  bool has_arg() const;

  void set_value(std::string const &value);
  void set_used(bool used);
  void set_required(bool required);
  void set_has_arg(bool has_arg);

  friend class DefaultParser;

private:
  std::string short_name_;
  std::string long_name_;
  std::string usage_;

  std::string value_;
  bool used_;

  bool required_;
  bool has_arg_;
};

} // namespace cli
} // namespace traceroute

#endif // TRACEROUTE_CLI_FLAG_HPP