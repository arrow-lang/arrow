// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_PRINT_H
#define ARROW_AST_PRINT_H

#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include "arrow/ast/nodes.hpp"

namespace arrow {
namespace ast {

class Print {
 public:
  Print();

  Print(const Print& other) = delete;
  Print(Print&& other) = delete;

  Print& operator=(const Print& other) = delete;
  Print& operator=(Print&& other) = delete;

  virtual ~Print() noexcept;

  void run(std::shared_ptr<Node> node);

 private:
  void print(std::shared_ptr<Node>);
  void print_module(std::shared_ptr<Module>);
  void print_variable(std::shared_ptr<Variable>);
  void print_integer(std::shared_ptr<Integer>);
  void print_type_name(std::shared_ptr<TypeName>);

  void handle(
    const char* name, std::shared_ptr<Node> n, std::function<void()> handle);

  rapidjson::StringBuffer _s;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> _w;
};

/// Helper function to construct and use an AST Printer.
inline void print(std::shared_ptr<Node> node) {
  Print().run(node);
}

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_PRINT_H
