#include "flags_usages.hpp"

#include <cli>
#include <net>
#include <internal>
#include <iostream>
#include <memory>

int main(int argc, char **argv) {

  traceroute::cli::Arguments args(argc, argv);
  traceroute::cli::Flags flags;

  traceroute::cli::Flag host_name("h", "host", true, HOST_FLAG_USAGE);
  host_name.set_required(true);
  flags.Add(host_name);

  traceroute::cli::Flag max_hops_num("mh", "max-hops", true, MAX_HOPS_USAGE);
  flags.Add(max_hops_num);

  traceroute::cli::Flag retry_timeout("rt", "retry-timeout", true,
                                      RETRY_TIMEOUT_USAGE);
  flags.Add(retry_timeout);

  traceroute::cli::Flag attempts_num("an", "attempts-num", true,
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

  std::string host = cmd.get_by_long_name("host").value();
  int ttl =
      traceroute::Conversion::Int(cmd.get_by_long_name("max-hops").value());
  int timeout = traceroute::Conversion::Int(
      cmd.get_by_long_name("retry-timeout").value());
  int attempts =
      traceroute::Conversion::Int(cmd.get_by_long_name("attempts-num").value());

  traceroute::net::Tracer tracer;
  tracer.Trace(host, std::cout);
}