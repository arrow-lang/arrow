
// Declare =====================================================================

// Declare: Integer, Signed
let i8: int8 = 10;
let i16: int16 = 1052;
let i32: int32 = 94;
let i64: int64 = 3425602;
let i128: int128 = 3290593290235;

// Declare: Integer, Unsigned
let u8: uint8 = 10;
let u16: uint16 = 1052;
let u32: uint32 = 94;
let u64: uint64 = 3425602;
let u128: uint128 = 3290593290235;

// Declare: Boolean
let b: bool = true;

// Declare: Real
let f32: float32 = 1e10;
let f64: float64 = 320.325;

// EqualTo =========================================================================

// EqualTo: Bool == Bool
b == b;

// EqualTo: Integer == Integer
i32 == i32;
u32 == u32;

// EqualTo: Integer == Literal Integer
i32 == 235;
3250 == u32;

// EqualTo: Literal Integer == Literal Integer
235 == 235;
3250 == 77634;

// EqualTo: Real == Real
f32 == f32;
f64 == f64;

// EqualTo: Real == Literal Real
f32 == 32.12;
325.12512 == f32;
f64 == 32.12;
325.12512 == f64;

// EqualTo: Real == Literal Integer
f32 == 213;
f64 == 31205;
213 == f32;
31205 == f64;

// EqualTo: Literal Real == Literal Integer
3.2362 == 3;
3235 == 3.512;

// NotEqualTo =========================================================================

// NotEqualTo: Bool != Bool
b != b;

// NotEqualTo: Integer != Integer
i32 != i32;
u32 != u32;

// NotEqualTo: Integer != Literal Integer
i32 != 235;
3250 != u32;

// NotEqualTo: Literal Integer != Literal Integer
235 != 235;
3250 != 77634;

// NotEqualTo: Real != Real
f32 != f32;
f64 != f64;

// NotEqualTo: Real != Literal Real
f32 != 32.12;
325.12512 != f32;
f64 != 32.12;
325.12512 != f64;

// NotEqualTo: Real != Literal Integer
f32 != 213;
f64 != 31205;
213 != f32;
31205 != f64;

// NotEqualTo: Literal Real != Literal Integer
3.2362 != 3;
3235 != 3.512;

// LessThan =========================================================================

// LessThan: Bool < Bool
b < b;

// LessThan: Integer < Integer
i32 < i32;
u32 < u32;

// LessThan: Integer < Literal Integer
i32 < 235;
3250 < u32;

// LessThan: Literal Integer < Literal Integer
235 < 235;
3250 < 77634;

// LessThan: Real < Real
f32 < f32;
f64 < f64;

// LessThan: Real < Literal Real
f32 < 32.12;
325.12512 < f32;
f64 < 32.12;
325.12512 < f64;

// LessThan: Real < Literal Integer
f32 < 213;
f64 < 31205;
213 < f32;
31205 < f64;

// LessThan: Literal Real < Literal Integer
3.2362 < 3;
3235 < 3.512;

// LessThanOrEqualTo =========================================================================

// LessThanOrEqualTo: Bool <= Bool
b <= b;

// LessThanOrEqualTo: Integer <= Integer
i32 <= i32;
u32 <= u32;

// LessThanOrEqualTo: Integer <= Literal Integer
i32 <= 235;
3250 <= u32;

// LessThanOrEqualTo: Literal Integer <= Literal Integer
235 <= 235;
3250 <= 77634;

// LessThanOrEqualTo: Real <= Real
f32 <= f32;
f64 <= f64;

// LessThanOrEqualTo: Real <= Literal Real
f32 <= 32.12;
325.12512 <= f32;
f64 <= 32.12;
325.12512 <= f64;

// LessThanOrEqualTo: Real <= Literal Integer
f32 <= 213;
f64 <= 31205;
213 <= f32;
31205 <= f64;

// LessThanOrEqualTo: Literal Real <= Literal Integer
3.2362 <= 3;
3235 <= 3.512;

// GreaterThan =========================================================================

// GreaterThan: Bool > Bool
b > b;

// GreaterThan: Integer > Integer
i32 > i32;
u32 > u32;

// GreaterThan: Integer > Literal Integer
i32 > 235;
3250 > u32;

// GreaterThan: Literal Integer > Literal Integer
235 > 235;
3250 > 77634;

// GreaterThan: Real > Real
f32 > f32;
f64 > f64;

// GreaterThan: Real > Literal Real
f32 > 32.12;
325.12512 > f32;
f64 > 32.12;
325.12512 > f64;

// GreaterThan: Real > Literal Integer
f32 > 213;
f64 > 31205;
213 > f32;
31205 > f64;

// GreaterThan: Literal Real > Literal Integer
3.2362 > 3;
3235 > 3.512;

// GreaterThanOrEqualTo =========================================================================

// GreaterThanOrEqualTo: Bool >= Bool
b >= b;

// GreaterThanOrEqualTo: Integer >= Integer
i32 >= i32;
u32 >= u32;

// GreaterThanOrEqualTo: Integer >= Literal Integer
i32 >= 235;
3250 >= u32;

// GreaterThanOrEqualTo: Literal Integer >= Literal Integer
235 >= 235;
3250 >= 77634;

// GreaterThanOrEqualTo: Real >= Real
f32 >= f32;
f64 >= f64;

// GreaterThanOrEqualTo: Real >= Literal Real
f32 >= 32.12;
325.12512 >= f32;
f64 >= 32.12;
325.12512 >= f64;

// GreaterThanOrEqualTo: Real >= Literal Integer
f32 >= 213;
f64 >= 31205;
213 >= f32;
31205 >= f64;

// GreaterThanOrEqualTo: Literal Real >= Literal Integer
3.2362 >= 3;
3235 >= 3.512;
