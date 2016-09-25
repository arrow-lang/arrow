// [ ] Pass: Declare
// [ ] Select (if)
// [x] Loop (while)
// [ ] Structure
// [ ] Main!

// [x] Parse: Mutable

// [x] Parse: TypePointer
// [ ] Parse: TypeRecord
// [ ] Parse: If
// [x] Parse: While
// [x] Build: TypePointer
// [ ] Build: If
// [x] Build: While
// [ ] Build: TypeRecord
// [x] Parse/Build: Address Of
// [x] Parse/Build: Dereference
// [ ] Parse/Build: Pointer Arithmetic

// [x] Cast: Primitive (function)
// [ ] Cast: Alias (pointer)

// [ ] Implicit cast to type alias from unnamed _literal_ of underlying type

extern def puts(s: str);
extern def printf(s: str, ...);

// let x: int8 = 0;
// printf("%d\n", x < 10 and false);
// printf("%d\n", x < 10 and true);

let cnt = if false {
  puts("then")
} else {
  puts("else")
}

// let x: int8 = 0;
// while x < 10 and false {
//   x = x + 1;
//   if x < 5 { continue; }
//   printf("Iterate: %d\n", x);
//   break;
// }
