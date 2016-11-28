import "std";

struct Point {
  x: int64;
  y: int64;
}

def double(mutable a: int64) {
  let b: int128 = 20;
  a = int64(b);
  twist(a);
}

def twist(mutable a: int64) {
  a <<= 2;
}

def setY(mutable p: Point): int64 {
  p.y = 123;
  return p.y;
}

def setX(mutable p: Point): int64 {
  p.x = 20;
  setY(p);
  twist(p.x);
  return p.x;
}

def main() {
  let a = 30;
  double(a);

  std.assert(a == 80);

  let p: Point;
  setX(p);

  std.assert(p.x == 80);
  std.assert(p.y == 123);
}
