
def methodA(): int64 {
  let value = if false { 302; } else { return 4; };
  return value;
}

def methodB(): int64 {
  let value = if true { return 30; } else { 320; };
  return value;
}

def methodC(): int64 {
  let check = true or (return 20);

  if check { return 310; }
  else { return 20; }
}

def methodD(): int64 {
  let unit = return 32;
}

def main() {
  methodA();
  methodB();
  methodC();
  methodD();
}
