
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

def test_if() {
  let rs: bool = if true { true; } else { false; };
  assert(rs);
}

def test_else() {
  let rs: bool = if false { false; } else { true; };
  assert(rs);
}

def test_elseif1() {
  let rs: bool = if true { true; } else if true { false; } else { false; };
  assert(rs);
}

def test_elseif2() {
  let rs: bool = if false { false; } else if true { true; } else { false; };
  assert(rs);
}

def test_elseif3() {
  let rs: bool = if false { false; } else if false { false; } else { true; };
  assert(rs);
}

def test_inferrence() {
  let rs = if true { true; } else { false; };
  assert(rs);
}

def test_if_as_if_condition() {
  let rs1: bool = if if false { false; } else { true; } { true; } else { false; };
  assert(rs1);
  let rs2: bool = if if true { false; } else { true; } { false; } else { true; };
  assert(rs2);
}

def test_if_as_block_result() {
  let rs: bool = if true { if false { false; } else { true; }; } else { false; };
  assert(rs);
}

def test_nested() {
  if false {
  assert(false);
  } else if false {
    assert(false);
  } else if false { assert(false); } else { assert(true); };
  if false { assert(false); } else if true { assert(true); };
  if false {
    assert(false);
  } else if true {
    if true {
      assert(true);
    } else { if false { assert(false); } else { assert(false); }; };
  };
  if false {
    assert(false);
  } else { if false { assert(false); } else { assert(true); }; };
}

def main() {
  test_if();
  test_else();
  test_elseif1();
  test_elseif2();
  test_elseif3();
  test_inferrence();
  test_if_as_if_condition();
  test_if_as_block_result();
  test_nested();
}

main();
