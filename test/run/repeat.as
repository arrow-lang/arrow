
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

def test_while() {
  let counter = 10;
  while counter != 0 {
    counter = counter - 1;
  }
  assert(counter == 0);
}

def test_while_continue() {
  let counter = 10;
  let foo = 321;
  while counter != 0 {
    counter = counter - 1;
    continue;
    foo = 123;
  }
  assert(foo == 321);
}

def test_while_break() {
  let counter = 10;
  while counter != 0 {
    counter = counter - 1;
    break;
  }
  assert(counter == 9);
}

def test_while_nested_continue() {
  let counter = 10;
  let foo = 10;
  let ase = 123;
  while counter != 0 {
    counter = counter - 1;
    while foo != 0 {
      foo = foo - 1;
      continue;
      ase = 321;
    }
  }
  assert(ase == 123);
}

def test_while_nested_break() {
  let counter = 5;
  let foo = 10;
  let ase = 123;
  while counter != 0 {
    counter = counter - 1;
    while foo != 0 {
      foo = foo - 1;
      break;
      ase = 321;
    }
  }
  assert(ase == 123);
  assert(foo == 5);
}

def main() {
  test_while();
  test_while_continue();
  test_while_break();
  test_while_nested_continue();
  test_while_nested_break();
}

main();
