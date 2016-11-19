import "std";

def main() {
  let mutable a: int32 = 1;
  let mutable b: int32 = 2;
  a = a ^ b;
  b = b ^ a;
  a = a ^ b;
  std.assert(b == 1);
  std.assert(a == 2);
  std.assert((~0xf0 & 0xff) == 0xf);
  std.assert((0xf0 | 0xf) == 0xff);
  std.assert((0b1010_1010 | 0b0101_0101) == 0xff);
}

main();
