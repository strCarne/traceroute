#include "flag.hpp"

namespace traceroute {
namespace cli {

Flag::Flag(std::string const &short_name, std::string const &long_name,
           bool has_arg, std::string const &usage)
    : short_name_(short_name), long_name_(long_name), usage_(usage), value_(""),
      used_(false), required_(false), has_arg_(has_arg) {}

Flag::Flag(std::string const &short_name, std::string const &long_name,
           std::string const &usage)
    : Flag(short_name, long_name, false, usage) {}

Flag::Flag(std::string const &name, bool has_arg, std::string const &usage)
    : Flag(name, name, has_arg, usage) {}

Flag::Flag(std::string const &name, std::string const &usage)
    : Flag(name, false, usage) {}

std::string const &Flag::short_name() const { return short_name_; }
std::string const &Flag::long_name() const { return long_name_; }
std::string const &Flag::usage() const { return usage_; }
std::string const &Flag::value() const { return value_; }
bool Flag::used() const { return used_; }
bool Flag::required() const { return required_; }
bool Flag::has_arg() const { return has_arg_; }

void Flag::set_value(std::string const &value) { value_ = value; }
void Flag::set_used(bool used) { used_ = used; }
void Flag::set_required(bool required) { required_ = required; }
void Flag::set_has_arg(bool has_arg) { has_arg_ = has_arg; }

} // namespace cli
} // namespace traceroute