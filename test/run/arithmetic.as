
// TODO: assert built-in or something
extern def abort();

def assert(condition: bool) {
  if not condition {
    abort();
  }
}

def test() {
  let a: int8 = 10;

  assert(a == 10);
  assert(a * (a - 1) == 90);
}

def sat_add(x: uint32): uint32 {
  let ret: uint32 = x + 1;
  return if ret < x { x; } else { ret; };
}

def test_sat_add() {
  let neg: uint32 = -1;
  assert(sat_add(neg) == neg);
}

def test_signed() {
  let i8: int8 = 10;
  let i16: int16 = 2000;
  let i32: int32 = 300000;
  let i64: int64 = 4000000000;
  let i128: int128 = 50000000000000000000;

  assert(i8 + 5 == 15);
  assert(i16 + 1000 == 3000);
  assert(i32 + 150000 == 450000);
  assert(i64 + 2000000000 == 6000000000);
  assert(i128 + 25000000000000000000 == 75000000000000000000);

  assert(i8 - 5 == 5);
  assert(i16 - 1000 == 1000);
  assert(i32 - 150000 == 150000);
  assert(i64 - 2000000000 == 2000000000);
  assert(i128 - 25000000000000000000 == 25000000000000000000);

  assert(i8 * 2 == 20);
  assert(i16 * 3 == 6000);
  assert(i32 * 4 == 1200000);
  assert(i64 * 5 == 20000000000);
  assert(i128 * 6 == 300000000000000000000);

  // NOTE: This is floor division
  assert(i8 / 2 == 5);
  assert(i16 / 3 == 666);
  assert(i32 / 4 == 75000);
  assert(i64 / 5 == 800000000);
  assert(i128 / 6 == 8333333333333333333);

  assert(i8 % 2 == 0);
  assert(i16 % 3 == 2);
  assert(i32 % 4 == 0);
  assert(i64 % 5 == 0);
  assert(i128 % 6 == 2);
}

def test_unsigned() {
  let u8: uint8 = 10;
  let u16: uint16 = 2000;
  let u32: uint32 = 300000;
  let u64: uint64 = 4000000000;
  let u128: uint128 = 50000000000000000000;

  assert(u8 + 5 == 15);
  assert(u16 + 1000 == 3000);
  assert(u32 + 150000 == 450000);
  assert(u64 + 2000000000 == 6000000000);
  assert(u128 + 25000000000000000000 == 75000000000000000000);

  assert(u8 - 5 == 5);
  assert(u16 - 1000 == 1000);
  assert(u32 - 150000 == 150000);
  assert(u64 - 2000000000 == 2000000000);
  assert(u128 - 25000000000000000000 == 25000000000000000000);

  assert(u8 * 2 == 20);
  assert(u16 * 3 == 6000);
  assert(u32 * 4 == 1200000);
  assert(u64 * 5 == 20000000000);
  assert(u128 * 6 == 300000000000000000000);

  // NOTE: This is floor division
  assert(u8 / 2 == 5);
  assert(u16 / 3 == 666);
  assert(u32 / 4 == 75000);
  assert(u64 / 5 == 800000000);
  assert(u128 / 6 == 8333333333333333333);

  assert(u8 % 2 == 0);
  assert(u16 % 3 == 2);
  assert(u32 % 4 == 0);
  assert(u64 % 5 == 0);
  assert(u128 % 6 == 2);
}

def main() {
  test();
  test_sat_add();
  test_signed();
  test_unsigned();
}
