#include "flags.hpp"

namespace traceroute {
namespace cli {

void Flags::Add(Flag const &flag) {
  flags_.push_back(flag);

  short_flags_.insert({flag.short_name(), &flags_.back()});
  long_flags_.insert({flag.long_name(), &flags_.back()});
  if (flag.required()) {
    required_flags_.push_back(&flags_.back());
  }
}

bool Flags::HasShortName(std::string const &short_name) const {
  return short_flags_.contains(short_name);
}

bool Flags::HasLongName(std::string const &long_name) const {
  return long_flags_.contains(long_name);
}

bool Flags::HasName(std::string const &name) const {
  return HasShortName(name) || HasLongName(name);
}

Flag const &Flags::get_by_short_name(std::string const &short_name) const {
  return *short_flags_.at(short_name);
}

Flag const &Flags::get_by_long_name(std::string const &long_name) const {
  return *long_flags_.at(long_name);
}

Flag const &Flags::get_by_name(std::string const &name) const {
  Flag *flag = short_flags_.at(name);
  if (flag != nullptr) {
    return *flag;
  }
  return *long_flags_.at(name);
}

std::string Flags::FormUsage() const {
  std::stringstream out;

  out << "Usage:\n";

  for (Flag const &flag : flags_) {
    out << kUsagePrefix;
    out << '-' << flag.short_name();
    out << ", --" << flag.long_name();
    out << ": " << flag.usage();
    out << '\n';
  }

  return out.str();
}

} // namespace cli
} // namespace traceroute