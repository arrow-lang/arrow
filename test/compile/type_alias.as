
// Alias
type c_int = int32;
type c_long = int64;
type c_llong = int128;

// Declare
let a: c_int = c_int(30);
let b: c_int = a;
let c: int32 = int32(a);
let d: int32 = 310;
let e: c_int = c_int(d);

// Assign
let f: c_llong = c_llong(3);
f = c_llong(e);
f = c_llong(a);
f = c_llong(210);
f = c_llong(30);
f = c_llong(int64(int32(c_int(10))));
