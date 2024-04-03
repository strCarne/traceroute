#include "arguments.hpp"

namespace traceroute {
namespace cli {

Arguments::Arguments(int argc, char **argv) {
  args_.reserve(argc);
  for (char **arg = argv; arg != argv + argc; ++arg) {
    args_.emplace_back(*arg);
  }
}

} // namespace cli
} // namespace traceroute