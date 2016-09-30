
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

// TODO: Default a1 and a2
def fibonacci(n: int64, a1: int64, a2: int64): int64 {
  // TODO: Return IF expression
  if n == 0 { return a1; }
  else { return fibonacci(n - 1, a2, a1 + a2); };
}

assert(fibonacci( 0, 1, 1) ==               1);
assert(fibonacci( 1, 1, 1) ==               1);
assert(fibonacci( 2, 1, 1) ==               2);
assert(fibonacci( 3, 1, 1) ==               3);
assert(fibonacci( 4, 1, 1) ==               5);
assert(fibonacci( 5, 1, 1) ==               8);
assert(fibonacci( 6, 1, 1) ==              13);
assert(fibonacci( 7, 1, 1) ==              21);
assert(fibonacci( 8, 1, 1) ==              34);
assert(fibonacci( 9, 1, 1) ==              55);
assert(fibonacci(10, 1, 1) ==              89);
assert(fibonacci(30, 1, 1) ==         1346269);
assert(fibonacci(40, 1, 1) ==       165580141);
assert(fibonacci(50, 1, 1) ==     20365011074);
assert(fibonacci(70, 1, 1) == 308061521170129);
