
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

let b0: bool = false;
let b1: bool = true;

let a: bool = b0 and b1;
let b: bool = b1 and b0;
let c: bool = b0 or b1;
let d: bool = b1 or b0;

assert(not a);
assert(not b);
assert(c);
assert(d);
