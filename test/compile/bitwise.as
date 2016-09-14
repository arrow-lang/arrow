
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

// Not ====================================================================

// Not: Integer
~i32;
~i128;

// Not: Literal Integer
~3043592358825323;

// And =========================================================================

// And: Integer + Integer
i32 & i32;
u32 & u32;

// And: Integer + Literal Integer
i32 & 235;
3250 & u32;

// And: Literal Integer + Literal Integer
235 & 235;
3250 & 77634;

// And: Bool + Bool
b & true;
false & b;
false & true;

// Or =========================================================================

// Or: Integer + Integer
i32 | i32;
u32 | u32;

// Or: Integer + Literal Integer
i32 | 235;
3250 | u32;

// Or: Literal Integer + Literal Integer
235 | 235;
3250 | 77634;

// Or: Bool + Bool
b | true;
false | b;
false | true;

// Xor =========================================================================

// Xor: Integer + Integer
i32 ^ i32;
u32 ^ u32;

// Xor: Integer + Literal Integer
i32 ^ 235;
3250 ^ u32;

// Xor: Literal Integer + Literal Integer
235 ^ 235;
3250 ^ 77634;

// Xor: Bool + Bool
b ^ true;
false ^ b;
false ^ true;
