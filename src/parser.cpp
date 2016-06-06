// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <boost/filesystem.hpp>

#include <string>

#include "arrow/parser.hpp"

using arrow::Parser;
namespace fs = boost::filesystem;

Parser::Parser(
  std::shared_ptr<std::istream> is, const std::string& filename
) : _t(is, filename) {
}

auto Parser::parse() -> std::shared_ptr<ast::Node> {
  // Declare the top-level, automatic module
  // The name of the module is built from the name of the given file
  auto stem = fs::path(_t._filename).stem().string();
  auto mod = std::make_shared<ast::Module>(Span(_t._filename), stem);

  // Attempt to match statements until the end of the stream
  while (!_t.empty()) {
    // Parse a statement (try)
    auto statement = parse_statement();
    if (statement) {
      // Add it to the module
      mod->statements.push_back(statement);
    }
  }

  return mod;
}
