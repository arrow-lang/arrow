// [ ] Variable declaration
let name: type = expression;

// [ ] Basic types (arrow)
/*

byte (8-bit, unsigned)
bool (1-bit[*])

int8
int16
int32
int64
int128

uint8
uint16
uint32
uint64
uint128

intptr (size of a pointer, signed)
uintptr (size of a pointer, unsigned)

char (32-bit, unsigned)

float16
float32
float64
float128

*/

// [ ] Expressions
// [ ]    - Add
// [ ]    - Subtract
// [ ]    - Multiply
// [ ]    - Divide
// [ ]    - Modulo
// [ ]    - Logical And
// [ ]    - Logical Or
// [ ]    - Logical Not
// [ ]    - Relational GT
// [ ]    - Relational GE
// [ ]    - Relational LT
// [ ]    - Relational LE
// [ ]    - Relational And
// [ ]    - Relational Or
// [ ]    - Bitwise And
// [ ]    - Bitwise Or
// [ ]    - Bitwise Xor
// [ ]    - Bitwise Not

// [ ] Pointers
// [ ]    - Type
// [ ]    - Address Of
// [ ]    - Dereference

// [ ] Cast

// [ ] Function declaration
def main() {
}

// [ ] Extern function declaration
extern def puts(s: *byte);

// [ ] Extern function declaration w/ABI
extern "stdcall" def CreateWindowExA();

// [ ] Function call (extern AND local)
main();
puts("Hello");

// [ ] Extern import
extern import "stdint.h";

// [ ] Module (namespace)
module cstdint { extern import "stdint.h"; }

// [ ] c module (built-in)
import "c";

/*

// [ ] Basic types (in C)
c.char
c.uchar
c.schar
c.int
c.uint
c.short
c.ushort
c.long
c.ulong
c.float
c.double
c.ldouble

*/

// [ ] BigInt
int  // (∞-bit, signed)
