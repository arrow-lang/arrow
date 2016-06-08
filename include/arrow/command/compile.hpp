// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_COMMAND_COMPILE_H
#define ARROW_COMMAND_COMPILE_H

#include "arrow/command.hpp"

namespace arrow {
namespace command {

class Compile : public InputCommand {
 public:
  Compile() { }

  virtual ~Compile() noexcept;

  Compile(const Compile& other) = delete;
  Compile(Compile&& other) = delete;

  Compile& operator=(const Compile& other) = delete;
  Compile& operator=(Compile&& other) = delete;

  virtual const char* name() const noexcept {
    return "compile";
  }

  virtual const char* description() const noexcept {
    return "Compile the input file";
  }

 private:
  virtual int run_with_input(
    std::shared_ptr<std::istream> is,
    const boost::program_options::variables_map& vm);
};

}  // namespace command
}  // namespace arrow

#endif  // ARROW_COMMAND_COMPILE_H
