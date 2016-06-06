// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <vector>
#include <string>

#include "arrow/command/parse.hpp"
#include "arrow/log.hpp"
#include "arrow/parser.hpp"
#include "arrow/ast/print.hpp"

using arrow::command::Parse;
namespace po = boost::program_options;

Parse::~Parse() noexcept { }

int Parse::run_with_input(
  std::shared_ptr<std::istream> is, const po::variables_map& vm
) {
  // Parse a node from the input stream
  auto node = arrow::parse(is, vm["input-file"].as<std::string>());

  // Print the AST to stdout
  ast::print(node);

  return arrow::Log::get().count(arrow::LOG_ERROR) > 0 ? EXIT_FAILURE : 0;
}
