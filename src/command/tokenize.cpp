// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <vector>
#include <string>

#include "cppformat/format.h"

#include "arrow/command/tokenize.hpp"
#include "arrow/tokenizer.hpp"
#include "arrow/log.hpp"

using arrow::command::Tokenize;
namespace po = boost::program_options;

Tokenize::~Tokenize() noexcept { }

int Tokenize::run_with_input(
  std::shared_ptr<std::istream> is, const po::variables_map& vm
) {
  // Build and bind a tokenizer to the input file
  arrow::Tokenizer tokenizer{is, vm["input-file"].as<std::string>()};

  // Enumerate until the end-of-file ..
  for (;;) {
    // .. read each token ..
    auto tok = tokenizer.pop();

    // .. and print them to stdout
    fmt::print("{}: {}\n", tok->span, *tok);

    if (tok->type == arrow::token::Type::End) { break; }
  }

  return arrow::Log::get().count(arrow::LOG_ERROR) > 0 ? EXIT_FAILURE : 0;
}
