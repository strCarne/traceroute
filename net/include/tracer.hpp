#ifndef TRACEROUTE_NET_TRACER_HPP
#define TRACEROUTE_NET_TRACER_HPP

#include "randomizer.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include <netdb.h>
#include <set>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>

namespace traceroute::net {

class Tracer {
public:
  Tracer(int max_ttl, int timeout, int attempts_num);
  Tracer();

  std::string Settings();

  void set_max_ttl(int max_ttl);
  void set_timeout(int timeout);
  void set_attempts_num(int attempts_num);

  void Trace(std::string const &host, std::ostream &out);

private:
  int max_ttl_;
  int timeout_;
  int attempts_num_;

  static const int kDefaultTTL = 64;
  static const int kDefaultTimeout = 3000;
  static const int kDefaultAttemptsNum = 3;

  static const int kBufferCapacity = 128;
};

} // namespace traceroute::net

#endif // TRACEROUTE_NET_TRACER_HPP