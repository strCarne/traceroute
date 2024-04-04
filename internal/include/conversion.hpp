#ifndef TRACEROUTE_INTERNAL_CONVERSION_HPP
#define TRACEROUTE_INTERNAL_CONVERSION_HPP

#include <algorithm>
#include <cctype>
#include <string>

namespace traceroute {

class Conversion {
public:
  static int Int(std::string s);
  static bool Bool(std::string s);
  static float Float(std::string s);

  static bool IsInteger(std::string const &s);
  static bool IsFloatingPoint(std::string const &s);

  static void Trim(std::string &s);
  static void ToLower(std::string &s);
};

} // namespace traceroute

#endif // TRACEROUTE_INTERNAL_CONVERSION_HPP