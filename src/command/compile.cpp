// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <vector>
#include <string>

#include "arrow/command/compile.hpp"
#include "arrow/log.hpp"
#include "arrow/parser.hpp"
#include "arrow/compiler.hpp"

using arrow::command::Compile;
namespace po = boost::program_options;

Compile::~Compile() noexcept { }

int Compile::run_with_input(
  ptr<std::istream> is, const po::variables_map& vm
) {
  // Compile the input file
  arrow::compile(is, vm["input-file"].as<std::string>());

  return arrow::Log::get().count(arrow::LOG_ERROR) > 0 ? EXIT_FAILURE : 0;
}
