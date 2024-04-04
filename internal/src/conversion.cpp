#include "conversion.hpp"

namespace traceroute {

int Conversion::Int(std::string s) {
  Trim(s);

  if (!IsInteger(s)) {
    return 0;
  }
  return std::stoi(s);
}

bool Conversion::Bool(std::string s) {
  Trim(s);
  ToLower(s);

  if (s == "true") {
    return true;
  } else if (s == "false") {
    return false;
  }

  return IsInteger(s) != 0;
}

float Conversion::Float(std::string s) {
  Trim(s);

  if (!IsFloatingPoint(s)) {
    return 0.0f;
  }
  return std::stof(s);
}

bool Conversion::IsInteger(std::string const &s) {
  if (s.length() < 1) {
    return false;
  }

  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    if (*it < '0' || '9' < *it) {
      return false;
    }
  }
  return true;
}

bool Conversion::IsFloatingPoint(std::string const &s) {
  if (s.length() < 1) {
    return false;
  }
  if (s[0] == '.' || s[s.length() - 1]) {
    return false;
  }

  bool dot_occured = false;
  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    if ('.' == *it) {
      if (dot_occured) {
        return false;
      }
      dot_occured = true;
    } else if (*it < '0' || '9' < *it) {
      return false;
    }
  }
}

void Conversion::Trim(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

void Conversion::ToLower(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(), std::tolower);
}

} // namespace traceroute