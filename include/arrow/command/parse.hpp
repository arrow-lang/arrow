// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_COMMAND_PARSE_H
#define ARROW_COMMAND_PARSE_H

#include "arrow/command.hpp"

namespace arrow {
namespace command {

class Parse : public InputCommand {
 public:
  Parse() { }

  virtual ~Parse() noexcept;

  Parse(const Parse& other) = delete;
  Parse(Parse&& other) = delete;

  Parse& operator=(const Parse& other) = delete;
  Parse& operator=(Parse&& other) = delete;

  virtual const char* name() const noexcept {
    return "parse";
  }

  virtual const char* description() const noexcept {
    return "Parse the input file and print the AST";
  }

 private:
  virtual int run_with_input(
    ptr<std::istream> is,
    const boost::program_options::variables_map& vm);
};

}  // namespace command
}  // namespace arrow

#endif  // ARROW_COMMAND_PARSE_H
