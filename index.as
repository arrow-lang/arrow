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
// [ ] Failed slots should create poison values (so as to not have spurious errors)
// [x] Auto-dereferencing of pointers during path expressions
// [x] Generic structures :: `struct Box<T> { }`
// [ ] Directory Import

// [X] Ternary Expressions {1}
// [-] implement T {2}
// [-] implement<T> Box<T> {3}
// [ ] TypeResolve for generic type parameters
// [ ] Record Literals -- Box{10}
// [-] Interfaces
// [ ] Resource Interface

struct Point {
  x: int64;
  y: int64;
}

struct Box<T> {
  value: T;
}

interface Resource {
  def release();
}

interface Sequence<T> {
  def length(): uint64;
}

implement Point {
  def new() {
    // [..]
  }
}

// implement Resource for Point {
//   def release(self) {
//     // [...]
//   }
// }

implement<T> Box<T> {
  // [...]
}

implement Box<bool> {
  // [...]
}

// implement<T> Sequence<T> for Box<T> {
//   // [...]
// }
