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

// import "libc";
import "vec";
import "./test";

struct Point {
  x: test.Box;
  y: int32;
}

// struct Record {
//   v: vec.Vector<Point>;
// }

// def get(): Point {
//   let p: Point;
//   return p;
// }

// implement Point {
//   def get(self): int64 {
//   }
// }

def main() {
  let p: Point;
  let v = *(p.x.a + 30);

  // let apx = get().x;
  // let r: Record;
  // r.v = vec.Vector<Point>.New();
  // let p: Point;
  // p.x = 230;
  // p.y = 40;
  // r.v.Push(p);
  //
  // // let ap = r.v.Get(0);
  // let apx = r.v.Get(0).x;
}
