import "std";

def test_bool() {
  std.assert(true == true);
  std.assert(false != true);
  std.assert((not true) == false);

  std.assert(not (true < false));
  std.assert(not (true <= false));
  std.assert(true > false);
  std.assert(true >= false);

  std.assert(false < true);
  std.assert(false <= true);
  std.assert(not (false > true));
  std.assert(not (false >= true));

  std.assert(not (false > true) & not (true < false));
  std.assert((false > true) | (true > false));
  std.assert((false < true) & (true > false));
  std.assert((not false) & true);
  std.assert(true & (not false));

  std.assert((false > true) | true);
  std.assert(true | (false > true));
  std.assert((not true) | true);
  std.assert(true | not true);
}

def test_int() {
  std.assert(12 == 12);
  std.assert(12 != 40);
  std.assert(not (12 == 40));

  std.assert(12 < 40);
  std.assert(40 > 12);
  std.assert(40 >= 40);
  std.assert(40 >= 34);
  std.assert(32 <= 32);
  std.assert(12 <= 32);

  std.assert((50 > 20) | (30 < 20));
  std.assert(not (40 == 30) & (30 > 20));
}

def test_real() {
  std.assert(12.15 == 12.15);
  std.assert(12.169 != 40.02);
  std.assert(40.20 != 40.02);
  std.assert(not (12.15 == 40));

  std.assert(12.12 < 40);
  std.assert(40 > 12.1);
  std.assert(40 >= 40.00);
  std.assert(40.120 >= 34.125);
  std.assert(32e-10 <= 32e+10);
  std.assert(12.32 <= 32);
}

def main() {
  test_bool();
  test_int();
  test_real();
}

main();
