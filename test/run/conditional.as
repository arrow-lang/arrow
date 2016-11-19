import "std";

def test_if() {
  let rs: bool = if true { true; } else { false; };
  std.assert(rs);
}

def test_else() {
  let rs: bool = if false { false; } else { true; };
  std.assert(rs);
}

def test_elseif1() {
  let rs: bool = if true { true; } else if true { false; } else { false; };
  std.assert(rs);
}

def test_elseif2() {
  let rs: bool = if false { false; } else if true { true; } else { false; };
  std.assert(rs);
}

def test_elseif3() {
  let rs: bool = if false { false; } else if false { false; } else { true; };
  std.assert(rs);
}

def test_inferrence() {
  let rs = if true { true; } else { false; };
  std.assert(rs);
}

def test_if_as_if_condition() {
  let rs1: bool = if if false { false; } else { true; } { true; } else { false; };
  std.assert(rs1);
  let rs2: bool = if if true { false; } else { true; } { false; } else { true; };
  std.assert(rs2);
}

def test_if_as_block_result() {
  let rs: bool = if true { if false { false; } else { true; }; } else { false; };
  std.assert(rs);
}

def test_nested() {
  if false {
  std.assert(false);
  } else if false {
    std.assert(false);
  } else if false { std.assert(false); } else { std.assert(true); };
  if false { std.assert(false); } else if true { std.assert(true); };
  if false {
    std.assert(false);
  } else if true {
    if true {
      std.assert(true);
    } else { if false { std.assert(false); } else { std.assert(false); }; };
  };
  if false {
    std.assert(false);
  } else { if false { std.assert(false); } else { std.assert(true); }; };
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
