// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <boost/filesystem.hpp>

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;
namespace fs = boost::filesystem;

Parser::Parser(
  ptr<std::istream> is, const std::string& filename
) : _t(is, filename) {
}

auto Parser::parse() -> ptr<ast::Module> {
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

      // Extend the module span
      mod->span = mod->span.extend(statement->span);
    }
  }

  return mod;
}

auto Parser::expect(token::Type type, bool consume) -> ptr<token::Token> {
  return expect({type}, consume);
}

auto Parser::expect(
  std::initializer_list<token::Type> types, bool consume
) -> ptr<token::Token> {
  std::vector<token::Type> types_v(types);
  return expect(types_v, consume);
}

auto Parser::expect(
  std::vector<token::Type> types, bool consume
) -> ptr<token::Token> {
  auto tok = consume ? _t.pop() : _t.peek();

  if (std::find(types.begin(), types.end(), tok->type) == types.end()) {
    if (types.size() == 1) {
      Log::get().error(tok->span, "expected {}, found {}", types[0], tok->type);
    } else {
      std::stringstream msg;
      msg << "expected one of ";

      unsigned index = 0;
      for (auto& type : types) {
        msg << type;
        if (index != 0) {
          msg << ", ";
        }

        index += 1;
      }

      msg << "; found " << tok->type;
      Log::get().error(tok->span, msg.str().c_str());
    }


    return nullptr;
  }

  return tok;
}
