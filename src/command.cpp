// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>
#include <fstream>

#include "arrow/command.hpp"
#include "arrow/log.hpp"

using arrow::Command;
using arrow::InputCommand;
namespace po = boost::program_options;

Command::~Command() noexcept { }

int Command::operator()(int argc, char** argv, char** environ) {
  // Declare option structures
  po::options_description desc;
  po::positional_options_description p;

  // Allow commands to add their own options
  add_options(desc, p);

  try {
    // Process command-line arguments against the described options
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
      .options(desc)
      .positional(p)
      .run(),
    vm);
    po::notify(vm);

    // Run our command
    return run(vm);
  } catch(po::unknown_option& uo) {
    Log::get().error(uo.what());
    return EXIT_FAILURE;
  }
}

InputCommand::~InputCommand() noexcept { }

void InputCommand::add_options(
  po::options_description& o,
  po::positional_options_description& p
) {
  // Add "input-file"
  o.add_options()("input-file", po::value<std::string>());
  p.add("input-file", 1);
}

int InputCommand::run(const boost::program_options::variables_map& vm) {
  // Bind our input_file to an input_stream
  // TODO(mehcode): Check for no file passed (and use stdin)
  auto input_file = vm["input-file"].as<std::string>();
  auto is = std::make_shared<std::ifstream>(input_file);
  if (!is->is_open()) {
    Log::get().error(
      "couldn't read \"{}\"; couldn't open path as file", input_file);

    return EXIT_FAILURE;
  }

  return run_with_input(is, vm);
}
