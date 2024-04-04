#ifndef TRACEROUTE_INTERNAL_RANDOMIZER_HPP
#define TRACEROUTE_INTERNAL_RANDOMIZER_HPP

#include <random>

namespace traceroute {

class Randomizer {
public:
  Randomizer();

  int NumRange(int low, int high);
private:
  std::mt19937 gen;
};

} // namespace traceroute

#endif // TRACEROUTE_INTERNAL_RANDOMIZER_HPP