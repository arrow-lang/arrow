
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

// TODO: C memory methods should come from cimport
extern def malloc(size: int64): *int8;
extern def free(ptr: *int8);

extern def printf(s: str, ...);

def test_simple() {
  let a: int32 = 1204;
  let p_a: *int32 = &a;

  let b = *p_a;
  let c: **int32 = &p_a;
  let d: int32 = **c;

  *p_a = 320;
  *c = &b;
  **c = 2301;

  assert(b == 2301);
  assert(a == 320);
  assert(c == &p_a);
  assert(*c == &b);
  assert(d == 1204);
}

def test_relational() {
  let a = 54;
  let p1a = &a;
  let p2a = &a;
  let p3a = p2a;
  let b = *p1a;
  let p1b = &b;
  let m = malloc(10);

  // EQ
  assert(p1a == p2a);
  assert(p2a == p3a);

  // NE
  assert(p1b != p1a);

  // LT
  assert(m < (m + 1));
  assert(m + 3 < m + 9);

  // LE
  assert(m <= m);

  // LT
  assert((m + 2) > (m + 1));
  assert(m + 3 > m - 9);

  // LE
  assert(m >= m);

  free(m);
}

def test_ptrdiff() {
  let m = malloc(10);
  let v: int128 = 20;

  assert((m - (m + 10)) == -10);
  assert(((m + 10) - m) == +10);
  assert(&v - (&v + 1) == -1);
  assert((&v as *int8) - ((&v + 1) as *int8) == -16);

  free(m);
}

// NOTE: ptr transmute will eventually be non-syntax (eg. `std.ptr.transmute`)
//       or similar when we have generics
def test_transmute() {
  let z = 0;
  let zp = &z as *int8;
  let ip = zp as *bool;

  assert(*ip == false);

  z = 1;

  assert(*ip == true);
}

def main() {
  test_simple();
  test_relational();
  test_ptrdiff();
  test_transmute();
}

main();
