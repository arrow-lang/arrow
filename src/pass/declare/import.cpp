// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "config.h"

#include "arrow/pass/declare.hpp"
#include "arrow/log.hpp"
#include "arrow/parser.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

using arrow::pass::Declare;
namespace fs = boost::filesystem;

// NOTE: Taken from: http://stackoverflow.com/a/29221546
static fs::path relativeTo(fs::path from, fs::path to)
{
   // Start at the root path and while they are the same then do nothing then
   // when they first diverge take the remainder of the two path and replace
   // the entire from path with ".."
   // segments.
   fs::path::const_iterator fromIter = from.begin();
   fs::path::const_iterator toIter = to.begin();

   // Loop through both
   while (fromIter != from.end() && toIter != to.end() && (*toIter) == (*fromIter))
   {
      ++toIter;
      ++fromIter;
   }

   fs::path finalPath;
   while (fromIter != from.end())
   {
      finalPath /= "..";
      ++fromIter;
   }

   while (toIter != to.end())
   {
      finalPath /= *toIter;
      ++toIter;
   }

   return finalPath;
}

static bool ends_with(const std::string& value, const std::string& ending) {
  if (ending.size() > value.size()) return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void Declare::visit_import(ptr<ast::Import> x) {
  std::string r_pathname;
  std::string r_path;

  if (boost::starts_with(x->source, "./")) {
    // Relative: Build path based on cwd of file
    auto base_dir = fs::path(x->span.filename).parent_path();
    auto path = fs::absolute(x->source, base_dir);
    if (!ends_with(x->source, ".as")) {
      path += ".as";
    }

    try {
      // Try the exact filename
      r_path = fs::canonical(path).string();
    } catch (fs::filesystem_error) {
      Log::get().error(
        x->span, "no module found for \"{}\"", x->source.c_str());

      return;
    }

    // Relativize the filename from the CWD
    boost::filesystem::path full_path(boost::filesystem::current_path());
    r_pathname = "./" + relativeTo(full_path, r_path).string();
  } else {
    // Absolute: Build path based on {PREFIX}
    auto base_dir = fs::path(WAF_PREFIX).append("lib/arrow/modules");
    auto path = fs::absolute("./" + x->source, base_dir);
    if (!ends_with(x->source, ".as")) {
      path += ".as";
    }

    try {
      // Try the exact filename
      r_path = fs::canonical(path).string();
    } catch (fs::filesystem_error) {
      Log::get().error(
        x->span, "no module found for \"{}\"", x->source.c_str());

      return;
    }

    // Use module source name here
    r_pathname = x->source;
  }

  // Check if this has been imported before (by the whole program)
  auto& current_mod = _ctx.module_s.top();
  auto ref = _ctx.modules_by_pathname.find(r_path);
  ptr<ir::Module> r_module;

  if (ref != _ctx.modules_by_pathname.end()) {
    r_module = ref->second;

    // Check if this is this module
    if (r_module.get() == current_mod.get()) {
      // Same module
      Log::get().error(x->span, "module cannot import self");
      return;
    }

    // TODO: Check if this has been imported before (by this module) [warn]
  } else {
    // Parse the AST from this file
    auto input_fs = new std::ifstream(r_path);
    std::shared_ptr<std::istream> input_stream(input_fs);
    arrow::Parser parser(input_stream, r_pathname);
    auto imp = parser.parse();
    if (!imp) return;

    // Create module item; add to (top-level) scope; cache
    r_module = make<ir::Module>(imp, imp->name, fs::change_extension(r_pathname, "").string());
    ir::Scope::top(_ctx.scope)->put(imp, r_module, "");
    _ctx.modules_by_pathname[r_path] = r_module;

    // Declare this module item
    Declare(_ctx).run(imp);
  }

  // Emplace the imported module in scope of the current module
  auto item = make<ir::Import>(x, r_module);
  _ctx.scope->put(x, item, r_module->name);
}
