// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_COMMAND_H
#define ARROW_COMMAND_H

#include "boost/program_options.hpp"

namespace arrow {

class Command {
 public:
  Command() { }

  virtual ~Command() noexcept;

  Command(const Command& other) = delete;
  Command(Command&& other) = delete;
  Command& operator=(const Command& other) = delete;
  Command& operator=(Command&& other) = delete;

  /// Name of the command (for use in `help`).
  virtual const char* name() const noexcept = 0;

  /// Description of the command (for use in `help`).
  virtual const char* description() const noexcept = 0;

  /// Run the command and return its result.
  int operator()(int argc, char** argv, char** environ);

 private:
  virtual void add_options(
    boost::program_options::options_description&,
    boost::program_options::positional_options_description&
  ) { }

  virtual int run(const boost::program_options::variables_map& vm) = 0;
};

/// Specialization of Command that expects an input-file as a positional
/// option
class InputCommand : public Command {
 public:
  InputCommand() { }

  virtual ~InputCommand() noexcept;

  InputCommand(const InputCommand& other) = delete;
  InputCommand(InputCommand&& other) = delete;
  InputCommand& operator=(const InputCommand& other) = delete;
  InputCommand& operator=(InputCommand&& other) = delete;

  /// Name of the command (for use in `help`).
  virtual const char* name() const noexcept = 0;

  /// Description of the command (for use in `help`).
  virtual const char* description() const noexcept = 0;

 private:
  virtual void add_options(
    boost::program_options::options_description&,
    boost::program_options::positional_options_description&);

  virtual int run(const boost::program_options::variables_map& vm);

  virtual int run_with_input(
    std::shared_ptr<std::istream> is,
    const boost::program_options::variables_map& vm) = 0;
};

}  // namespace arrow

#endif  // ARROW_COMMAND_H

#include "arrow/command/tokenize.hpp"
#include "arrow/command/parse.hpp"
// #include "arrow/command/compile.hpp"
// #include "arrow/command/run.hpp"
