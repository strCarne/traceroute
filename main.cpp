#include "flags_usages.hpp"

#include <cli>
#include <iostream>

int main(int argc, char **argv) {

  traceroute::cli::Arguments args(argc, argv);
  traceroute::cli::Flags flags;

  traceroute::cli::Flag host_name("h", "host", true, HOST_FLAG_USAGE);
  host_name.set_required(true);
  flags.Add(host_name);

  traceroute::cli::Parser *parser = new traceroute::cli::DefaultParser();

  traceroute::cli::CommandLine cmd;
  try {
    cmd = parser->Parse(args, flags);
  } catch (...) {
    std::cerr << flags.FormUsage();
    delete parser;
    return -1;
  }
  delete parser;

  std::string host = cmd.get_by_long_name("host").value();
  std::cout << host << '\n';
}