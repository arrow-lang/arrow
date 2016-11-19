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

// [ ] Auto-dereferencing of pointers during path expressions
// [ ] Ternary Expressions
// [ ] Generic structures :: `struct Box<T> { }`
// [ ] Implement
// [ ] Generic Implement
// [ ] Directory Import

import "std";
import "libc";

struct Vector<T> {
  capacity: uint64;
  size: uint64;
  element_size: uint64;
  data: *T;
}

def vector_new<T>(): Vector<T> {
  // return Vector{
  //   // [...]
  //   element_size: std.size_of<T>(),
  // };

  let v: Vector<T>;
  v.capacity = 0;
  v.size = 0;
  v.element_size = std.size_of<T>();
  v.data = std.null<T>();

  return v;
}

// def vector_reserve(self: *Vector<T>, capacity: uint64) {
//   // Check existing capacity
//   if capacity <= (*self).capacity { return; }
//
//   // Ensure that we allocate in chunks of <CHUNK>
//   // FIXME: Requesting 10, allocates 20
//   (*self).capacity = capacity + (10 - (capacity % 10));
//
//   // Reallocate memory
//   (*self).data = libc.realloc(
//     (*self).data, (*self).capacity * (*self).element_size);
// }
//
// def vector_push<T>(self: *Vector<T>, element: T) {
//   // Request additional memory (if needed)
//   vector_reserve(self, (*self).capacity + 1);
//
//   // Move element into the container
//   let offset = (*self).size * (*self).element_size;
//   libc.memcpy(((*self).data + offset) as *uint8, &element as *uint8, (*self).element_size);
//
//   // Increment size to keep track of element insertion
//   (*self).size += 1;
// }

// def vector_size<T>(self: *Vector<int32>): uint64 {
//   return (*self).size;
// }

// def vector_get<T>(self: *Vector<T>, index: uint64): T {
//   let offset = index * (*self).element_size;
//
//   return *(((*self).data + offset) as *T);
// }
//
def main() {
  let v = vector_new<int32>();

  libc.srand(uint32(libc.time(std.null<int64>())));

  // let i2 = 0;
  // while i2 < 25 {
  //   vector_push<int32>(&v, int32(libc.rand()) % 100);
  //   i2 += 1;
  // }

  // libc.printf("[%d]int32 {\n", vector_size(&v));

  // let i = 0;
  // while i < vector_size(&v) {
  //   let el = vector_get<int32>(&v, i);
  //
  //   libc.printf("\t[%d] = %d\n", i, el);
  //
  //   i += 1;
  // }

  libc.printf("}\n");
}
