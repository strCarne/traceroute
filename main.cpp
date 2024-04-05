#include "flags_usages.hpp"

#include <cli>
#include <internal>
#include <iostream>
#include <memory>
#include <net>
#include <sstream>

int main(int argc, char **argv) {

  traceroute::cli::Arguments args(argc, argv);
  traceroute::cli::Flags flags;

  traceroute::cli::Flag max_hops_num("m", "max-hops", true, MAX_HOPS_USAGE);
  flags.Add(max_hops_num);

  traceroute::cli::Flag retry_timeout("t", "timeout", true,
                                      RETRY_TIMEOUT_USAGE);
  flags.Add(retry_timeout);

  traceroute::cli::Flag attempts_num("a", "attempts-num", true,
                                     ATTEMPTS_NUM_USAGE);
  flags.Add(attempts_num);

  traceroute::cli::CommandLine cmd;
  try {
    std::unique_ptr<traceroute::cli::Parser> parser =
        std::make_unique<traceroute::cli::DefaultParser>();
    cmd = parser->Parse(args, flags);
  } catch (...) {
    std::cerr << flags.FormUsage();
    return -1;
  }

  int ttl = 0;
  int timeout = 0;
  int attempts = 0;

  ttl = traceroute::Conversion::Int(cmd.get_by_long_name("max-hops").value());
  timeout = traceroute::Conversion::Int(
      cmd.get_by_long_name("timeout").value());
  attempts =
      traceroute::Conversion::Int(cmd.get_by_long_name("attempts-num").value());

  traceroute::net::Tracer tracer;

  if (ttl > 0) {
    tracer.set_max_ttl(ttl);
  }

  if (timeout > 0) {
    tracer.set_timeout(timeout);
  }

  if (attempts > 0) {
    tracer.set_attempts_num(attempts);
  }

  if (cmd.arguments().size() < 1) {
    std::cerr << "err: no hosts provided.";
  }

  std::cout << tracer.Settings();

  for (std::string const &host : cmd.arguments()) {
    tracer.Trace(host, std::cout);
    std::cout << '\n';
  }
}