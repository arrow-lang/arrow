import "std";

def test_assign() {
  let mutable x: int32;
  let y: int32 = x = 10;
  let mutable z: int32;
  std.assert(x == 10);
  std.assert(y == 10);
  z = x = 11;
  std.assert(x == 11);
  std.assert(z == 11);
  z = x = 12;
  std.assert(x == 12);
  std.assert(z == 12);
}

def test_assign_op() {
  let mutable x: int32 = 0;
  let y: int32 = x += 10;
  let mutable z: int32;
  std.assert(x == 10);
  std.assert(y == 10);
  z = x += 11;
  std.assert(x == 21);
  std.assert(z == 21);
  z = x += 12;
  std.assert(x == 33);
  std.assert(z == 33);
}

def main() {
  test_assign();
  test_assign_op();
}

main();
