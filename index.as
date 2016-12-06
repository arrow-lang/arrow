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
// [x] implement T {2}
// [x] implement<T> Box<T> {3}
// [ ] TypeResolve for generic type parameters
// [ ] Record Literals -- Box{10}
// [-] Interfaces
// [ ] Resource Interface
// [ ] uintx / intx -> pointer-sized
// [ ] byte -> uint8
// [ ] c typedef should come across as a strong type alias
// [ ] Sequence failure (fix parsing after error)
// [ ] Records must be passed by-reference

// [ ] Namespace (allow for structs/functions inside function)

// [ ] Error on duplicate method names
// [ ] Error on method names conflicting with record member names
// [ ] Error on impl not in same module
// [ ] Error on impl not on user-defined-type

// [x] Hidden References and Mutable Parameters

// [ ] Function return should become address-able
// [ ] Instance methods MUST use self. to access
