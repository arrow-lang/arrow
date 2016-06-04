// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <cstdio>
#include <iostream>
#include <fstream>

#include "cppformat/format.h"
#include "arrow/tokenizer.hpp"

void help(char* binary_path) {
  std::printf(
    "Usage: \x1b[0;36m%s\x1b[0m [<command>] [<options>] <input-file>\n",
    binary_path);

  std::printf("\n");
}

int main(int argc, char** argv) {
  // help(argv[0]);

  auto stream = std::make_shared<std::fstream>(argv[1]);
  if (!stream->is_open()) {
    return -1;
  }

  arrow::Tokenizer tokenizer(stream, argv[1]);

  while (!tokenizer.empty()) {
    auto token = tokenizer.pop();

    fmt::print("{}: {}: {}\n", token->span, token->type, *token);
  }
}
