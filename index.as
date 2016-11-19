// [ ] Rename pass::Declare to pass::Expose
// [ ] Rename @::TypeRecord to @::Record
// [ ] IR -> source :: a SPAN (not the full AST node)
// [ ] Methods / Member Functions :: `implement T`
// [ ] Error: Use before declare (applies mainly to `let r = r * 2` cases)
// [ ] Structure return from function (direct via compressed integers or sret)
// [ ] Unit should be an empty llvm struct instead of <nothing>
// [ ] (from `#include`) `c_void` -> Alias to `()`
// [ ] Type alias of a type alias should refer to the canoncial type
// [x] `import ".."` cache
// [ ] `#include ".."` cache
// [x] `extern ..` cache
// [ ] (I)Resource :: acquire/release
// [ ] Failed slots should create poison values (so as to not have spurious errors)
// [x] Auto-dereferencing of pointers during path expressions
// [ ] Ternary Expressions
// [x] Generic structures :: `struct Box<T> { }`
// [ ] Implement
// [ ] Generic Implement
// [ ] Directory Import
