// [ ] IR -> source :: a SPAN (not the full AST node)
// [ ] Methods / Member Functions :: `implement T`
// [ ] Error: Use before declare (applies mainly to `let r = r * 2` cases)
// [ ] Structure return from function (direct via compressed integers or sret)
// [ ] Unit should be an empty llvm struct instead of <nothing>
// [ ] (from `#include`) `c_void` -> Alias to `()`
// [ ] Type alias of a type alias should refer to the canoncial type
// [ ] Generic structures :: `struct Box<T> { }`
// [x] `import ".."` cache
// [ ] `#include ".."` cache
// [x] `extern ..` cache
// [ ] Missing `;` after 1-line function w/return can segfault

// [ ] integer type resolution: `i` should be the type of `I`
// let i = 0;
// while i < 0x10 {
//   *((*c).V + i) = mmu.read(c, (*c).I + i);
//   i += 1;
// }
