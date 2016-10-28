// [ ] IR Source should be just a SPAN not the full AST node
// [x] Parse/Build: Pointer Arithmetic
// [x] Cast: Alias (pointer)
// [x] Relational: Pointer
// [ ] Unit should be an empty llvm struct instead of <nothing>
// [ ] Type alias of a type alias should refer to the canoncial type
// [x] Function "Objects"
// [x] Compound/Augmented Assignment `+=`
// [x] str is just a name for *int8 (not alias)
// [x] Implicit cast to type alias from unnamed _literal_ of underlying type
// [x] Arithmetic of named integer against literal
// [x] Relational of named integer against literal
// [x] If Expression
// [x] UNIT Type / Value
// [x] DIVERGENT Type / Value
// [x] Repeat: Break
// [x] Repeat: Continue
// [x]   `break` and `continue` are considered divergent (block)
// [x] warning: unreachable code
// [x] Type cast
// [x] Function hoisting segfaults compiler in type deduction
// [x] Parse: TypeFunction
// [x] Parse: TypeTuple
// [x] Parse: Augmented Assignment
// [ ] Parse: Structure
// [ ] Struct
// [ ] Implement (T)
// [ ] Augmented Assignment for `<<=` and `>>=`


// [ ] Functions can have generic type parameters `def method[..]`
// [ ] `Identifier` is wrapped in a `Name` object (that can optionally have type parameters)

extern def printf(format: str, ...);

def size_of[T](): int64 {
  return 0;
  // return int64((0 as *T) - ((0 as *T) + 1));
}

// printf("?       : %d\n", size_of());
printf("bool    : %d\n", size_of[bool]());

// printf("int128  : %d\n", size_of[int128]());
// printf("float32 : %d\n", size_of[float32]());
// printf("*int    : %d\n", size_of[*int]());
