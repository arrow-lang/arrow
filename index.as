// [ ] Pass: Declare
// [ ] Select (if)
// [ ] Loop (while)
// [ ] Pointer (*)
// [ ] Structure
// [ ] Main!

// [x] Parse: Mutable

// [ ] ABI to ExternFunction

// [ ] Parse: TypePointer
// [ ] Parse: TypeRecord
// [ ] Parse: If
// [ ] Parse: While
// [ ] Build: TypePointer
// [ ] Build: If
// [ ] Build: While
// [ ] Build: TypeRecord
// [ ] Parse/Build: Address Of
// [ ] Parse/Build: Dereference
// [ ] Parse/Build: Pointer Arithmetic

// [ ] Cast: Primitive (function)
// [ ] Cast: Alias (pointer)

// let a: int8 = 120;
// let mutable b: int16 = int16(a);
//
// let c: float32 = 3.125;
// let mutable d: float64 = float64(c);

extern "cdecl" def printf(s: str, ...);

printf("Hello, World!\n");
