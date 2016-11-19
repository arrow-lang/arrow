import "std";

def test() {
  let a: int8 = 10;

  std.assert(a == 10);
  std.assert(a * (a - 1) == 90);
}

def sat_add(x: uint32): uint32 {
  let ret: uint32 = x + 1;
  return if ret < x { x; } else { ret; };
}

def test_sat_add() {
  let neg: uint32 = -1;
  std.assert(sat_add(neg) == neg);
}

def test_signed() {
  let i8: int8 = 10;
  let i16: int16 = 2000;
  let i32: int32 = 300000;
  let i64: int64 = 4000000000;
  let i128: int128 = 500000000000;

  std.assert(i8 + 5 == 15);
  std.assert(i16 + 1000 == 3000);
  std.assert(i32 + 150000 == 450000);
  std.assert(i64 + 2000000000 == 6000000000);
  std.assert(i128 + 250000000000 == 750000000000);

  std.assert(i8 - 5 == 5);
  std.assert(i16 - 1000 == 1000);
  std.assert(i32 - 150000 == 150000);
  std.assert(i64 - 2000000000 == 2000000000);
  std.assert(i128 - 250000000000 == 250000000000);

  std.assert(i8 * 2 == 20);
  std.assert(i16 * 3 == 6000);
  std.assert(i32 * 4 == 1200000);
  std.assert(i64 * 5 == 20000000000);
  std.assert(i128 * 6 == 3000000000000);

  // NOTE: This is floor division
  std.assert(i8 / 2 == 5);
  std.assert(i16 / 3 == 666);
  std.assert(i32 / 4 == 75000);
  std.assert(i64 / 5 == 800000000);
  std.assert(i128 / 6 == 83333333333);

  std.assert(i8 % 2 == 0);
  std.assert(i16 % 3 == 2);
  std.assert(i32 % 4 == 0);
  std.assert(i64 % 5 == 0);
  std.assert(i128 % 6 == 2);
}

def test_unsigned() {
  let u8: uint8 = 10;
  let u16: uint16 = 2000;
  let u32: uint32 = 300000;
  let u64: uint64 = 4000000000;
  let u128: uint128 = 500000000000;

  std.assert(u8 + 5 == 15);
  std.assert(u16 + 1000 == 3000);
  std.assert(u32 + 150000 == 450000);
  std.assert(u64 + 2000000000 == 6000000000);
  std.assert(u128 + 250000000000 == 750000000000);

  std.assert(u8 - 5 == 5);
  std.assert(u16 - 1000 == 1000);
  std.assert(u32 - 150000 == 150000);
  std.assert(u64 - 2000000000 == 2000000000);
  std.assert(u128 - 250000000000 == 250000000000);

  std.assert(u8 * 2 == 20);
  std.assert(u16 * 3 == 6000);
  std.assert(u32 * 4 == 1200000);
  std.assert(u64 * 5 == 20000000000);
  std.assert(u128 * 6 == 3000000000000);

  // NOTE: This is floor division
  std.assert(u8 / 2 == 5);
  std.assert(u16 / 3 == 666);
  std.assert(u32 / 4 == 75000);
  std.assert(u64 / 5 == 800000000);
  std.assert(u128 / 6 == 83333333333);

  std.assert(u8 % 2 == 0);
  std.assert(u16 % 3 == 2);
  std.assert(u32 % 4 == 0);
  std.assert(u64 % 5 == 0);
  std.assert(u128 % 6 == 2);
}

def main() {
  test();
  test_sat_add();
  test_signed();
  test_unsigned();
}
