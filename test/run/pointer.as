import "std";
import "libc";

def test_simple() {
  let a = 1204;
  let p_a = &a;

  let b = *p_a;
  let c = &p_a;
  let d = **c;

  *p_a = 320;
  *c = &b;
  **c = 2301;

  std.assert(b == 2301);
  std.assert(a == 320);
  std.assert(c == &p_a);
  std.assert(*c == &b);
  std.assert(d == 1204);
}

def test_relational() {
  let a = 54;
  let p1a = &a;
  let p2a = &a;
  let p3a = p2a;
  let b = *p1a;
  let p1b = &b;
  let m = libc.malloc(10);

  // EQ
  std.assert(p1a == p2a);
  std.assert(p2a == p3a);

  // NE
  std.assert(p1b != p1a);

  // LT
  std.assert(m < (m + 1));
  std.assert(m + 3 < m + 9);

  // LE
  std.assert(m <= m);

  // LT
  std.assert((m + 2) > (m + 1));
  std.assert(m + 3 > m - 9);

  // LE
  std.assert(m >= m);

  libc.free(m);
}

def test_ptrdiff() {
  let m = libc.malloc(10);
  let v: int128 = 20;

  std.assert((m - (m + 10)) == -10);
  std.assert(((m + 10) - m) == +10);
  std.assert(&v - (&v + 1) == -1);
  std.assert((&v as *int8) - ((&v + 1) as *int8) == -16);

  libc.free(m);
}

// NOTE: ptr transmute will eventually be non-syntax (eg. `std.ptr.transmute`)
//       or similar when we have generics
def test_transmute() {
  let z = 0;
  let zp = &z as *int8;
  let ip = zp as *bool;

  std.assert(*ip == false);

  z = 1;

  std.assert(*ip == true);
}

struct Point {
  x: int32;
  y: int32;
}

def test_auto_indirect() {
  let m: Point;
  m.x = 10;

  let p = &m;
  p.y = 20;

  std.assert(p.x == 10);
  std.assert(m.y == 20);
}

def main() {
  test_simple();
  test_relational();
  test_ptrdiff();
  test_transmute();
  test_auto_indirect();
}

main();
