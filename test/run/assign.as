
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

def test_assign() {
  let mutable x: int32;
  let y: int32 = x = 10;
  let mutable z: int32;
  assert(x == 10);
  assert(y == 10);
  z = x = 11;
  assert(x == 11);
  assert(z == 11);
  z = x = 12;
  assert(x == 12);
  assert(z == 12);
}

def test_assign_op() {
  let mutable x: int32 = 0;
  let y: int32 = x += 10;
  let mutable z: int32;
  assert(x == 10);
  assert(y == 10);
  z = x += 11;
  assert(x == 21);
  assert(z == 21);
  z = x += 12;
  assert(x == 33);
  assert(z == 33);
}

def main() {
  test_assign();
  test_assign_op();
}

main();
