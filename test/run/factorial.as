import "std";

def factorial(n: int64): int64 {
  // TODO: Return the IF expression

  if n != 0 {
    return n * factorial(n - 1);
  } else {
    return 1;
  }
}

std.assert(factorial( 0) ==       1);
std.assert(factorial( 1) ==       1);
std.assert(factorial( 2) ==       2);
std.assert(factorial( 3) ==       6);
std.assert(factorial( 4) ==      24);
std.assert(factorial( 5) ==     120);
std.assert(factorial( 6) ==     720);
std.assert(factorial( 7) ==    5040);
std.assert(factorial( 8) ==   40320);
std.assert(factorial( 9) ==  362880);
std.assert(factorial(10) == 3628800);
