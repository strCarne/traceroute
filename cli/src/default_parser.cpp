#include "default_parser.hpp"
#include <iostream>

namespace traceroute {
namespace cli {

CommandLine DefaultParser::Parse(Arguments const &args, Flags const &flags) {
  CommandLine cmd;
  cmd.invoke_cmd_ = args.args_[0];

  std::vector<std::string> parsed_args;
  Flags parsed_flags;

  enum State { kNonArgFlag, kArgFlag, kInvalidFlag };
  auto handle_flag = [&parsed_flags, this](Flag flag, std::string const *next) {
    if (flag.has_arg() && next == nullptr) {
      throw "err: " + flag.long_name() + "doesn't have specified arg";
    }

    flag.set_used(true);

    if (!flag.has_arg()) {
      parsed_flags.Add(flag);
      return kNonArgFlag;
    }

    flag.set_value(*next);
    parsed_flags.Add(flag);

    return kArgFlag;
  };

  for (size_t i = 1; i < args.args_.size();) {
    std::string const &arg = args.args_[i];

    std::string const *next = nullptr;
    if (i + 1 != args.args_.size()) {
      next = &args.args_[i + 1];
    }

    if (arg.starts_with("--") && flags.HasLongName(arg.substr(2))) {
      Flag const &flag = flags.get_by_long_name(arg.substr(2));

      State state = handle_flag(flag, next);
      if (state == kNonArgFlag) {
        i++;
      } else {
        i += 2;
      }

    } else if (arg.starts_with("-") && flags.HasShortName(arg.substr(1))) {
      Flag const &flag = flags.get_by_short_name(arg.substr(1));

      State state = handle_flag(flag, next);
      if (state == kNonArgFlag) {
        i++;
      } else {
        i += 2;
      }
    } else {
      parsed_args.push_back(arg);
      i++;
    }
  }

  for (Flag const &f : flags.flags_) {
    if (!parsed_flags.HasLongName(f.long_name())) {
      if (f.required()) {
        std::cout << "WATAFAK " + f.long_name() + "\n";
        throw "err: couldn't find required flag" + f.long_name() + "\n";
      }
      parsed_flags.Add(f);
    }
  }

  cmd.args_.args_ = parsed_args;
  cmd.flags_ = parsed_flags;
  return cmd;
}

} // namespace cli
} // namespace traceroute