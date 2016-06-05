// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_COMMAND_TOKENIZE_H
#define ARROW_COMMAND_TOKENIZE_H

#include "arrow/command.hpp"

namespace arrow {
namespace command {

class Tokenize : public InputCommand {
 public:
  Tokenize() { }

  virtual ~Tokenize() noexcept;

  Tokenize(const Tokenize& other) = delete;
  Tokenize(Tokenize&& other) = delete;
  Tokenize& operator=(const Tokenize& other) = delete;
  Tokenize& operator=(Tokenize&& other) = delete;

  virtual const char* name() const noexcept {
    return "tokenize";
  }

  virtual const char* description() const noexcept {
    return "Tokenize the input file and print each token";
  }

 private:
  virtual int run_with_input(
    std::shared_ptr<std::istream> is,
    const boost::program_options::variables_map& vm);
};

}  // namespace command
}  // namespace arrow

#endif  // ARROW_COMMAND_TOKENIZE_H
