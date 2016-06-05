// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <vector>
#include <string>

#include "arrow/command/parse.hpp"
#include "arrow/log.hpp"

using arrow::command::Parse;
namespace po = boost::program_options;

Parse::~Parse() noexcept { }

int Parse::run_with_input(
  std::shared_ptr<std::istream> is, const po::variables_map& vm
) {
  // TODO:!
  return -1;
}
