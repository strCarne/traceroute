#include "randomizer.hpp"

namespace traceroute {

Randomizer::Randomizer() {
  std::random_device rd;
  gen = std::mt19937(rd());
}

int Randomizer::NumRange(int low, int high) {
  std::uniform_int_distribution<int> distr(low, high);
  return distr(gen);
}

} // namespace traceroute