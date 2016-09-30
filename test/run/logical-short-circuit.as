
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

let counter = 0;

if false or { counter = counter + 1; true; } {
  assert(true);
}

if true or { counter = counter + 1; false; } {
  assert(true);
}

if false and { counter = counter + 1; true; } {
  assert(false);
}

if true and { counter = counter + 1; true; } {
  assert(true);
}

assert(counter == 2);
