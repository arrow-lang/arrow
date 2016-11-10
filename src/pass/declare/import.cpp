// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"
#include "arrow/log.hpp"
#include "arrow/parser.hpp"

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
  // Build the absolute path of the file to import
  auto dir = fs::path(x->span.filename).parent_path();
  auto path = fs::absolute(x->source, dir);
  std::string pathname;

  // If 'source' did not end in '.as'; append '.as'
  if (!ends_with(x->source, ".as")) {
    path += ".as";
  }

  try {
    // Try the exact filename
    pathname = fs::canonical(path).string();
  } catch (fs::filesystem_error) {
    Log::get().error(
      x->span, "no module found for \"%s\"", x->source.c_str());

    return;
  }

  // TODO: Check if this has been imported before (by the whole program)
  // TODO:  -> Check if this is this module
  // TODO:  -> Check if this has been imported before (by this module)

  // Relativize the filename from the CWD
  boost::filesystem::path full_path(boost::filesystem::current_path());
  auto relpath = relativeTo(full_path, pathname);

  // Parse the AST from this file
  auto input_fs = new std::ifstream(pathname);
  std::shared_ptr<std::istream> input_stream(input_fs);
  arrow::Parser parser(input_stream, relpath.string());
  auto imp = parser.parse();
  if (!imp) return;

  // Declare this module item
  Declare(_ctx).run(imp);

  // Get: Module
  auto impmod = _ctx.scope->get<ir::Module>(imp);
  if (!impmod) return;

  // Emplace the imported module in scope of the current module
  auto item = make<ir::Import>(x, impmod);
  _ctx.scope->put(x, item, impmod->name);
}
