// [ ] Conditional – If
// [ ] Iteration – While
// [ ] Extern Function / Extern Call @mehcode
// [ ] Structure
// [ ] Pointers
// [ ] Float
// [ ] (C-)String
// [ ] Bitwise

// [ ] Integer literals should have their own type with a name of `_`
// [ ] Pass: Declare
// [ ] Main!

type c_int = int32;
extern def puts(s: str) -> c_int;

def method(a: int32) {
  return 30;
}

def main() {
  // let apple;
  // let banana: int8;
  // let car = method(20);
  let dollar: int32 = method(1);
  if dollar > 10 {
    puts("over");
  } else {
    puts("under");
  }
}

def test() {
  return false;
}
