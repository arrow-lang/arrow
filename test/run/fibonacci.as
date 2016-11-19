import "std";

// TODO: Default a1 and a2
def fibonacci(n: int64, a1: int64, a2: int64): int64 {
  return if n == 0 {
    a1;
  } else {
    fibonacci(n - 1, a2, a1 + a2);
  };
}

std.assert(fibonacci( 0, 1, 1) ==               1);
std.assert(fibonacci( 1, 1, 1) ==               1);
std.assert(fibonacci( 2, 1, 1) ==               2);
std.assert(fibonacci( 3, 1, 1) ==               3);
std.assert(fibonacci( 4, 1, 1) ==               5);
std.assert(fibonacci( 5, 1, 1) ==               8);
std.assert(fibonacci( 6, 1, 1) ==              13);
std.assert(fibonacci( 7, 1, 1) ==              21);
std.assert(fibonacci( 8, 1, 1) ==              34);
std.assert(fibonacci( 9, 1, 1) ==              55);
std.assert(fibonacci(10, 1, 1) ==              89);
std.assert(fibonacci(30, 1, 1) ==         1346269);
std.assert(fibonacci(40, 1, 1) ==       165580141);
std.assert(fibonacci(50, 1, 1) ==     20365011074);
std.assert(fibonacci(70, 1, 1) == 308061521170129);
