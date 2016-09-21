let a: int32 = 1204;
let p_a: *int32 = &a;

let b: int32 = *p_a;
let c: **int32 = &p_a;
let d: int32 = **c;

*p_a = 320;
*c = &b;
**c = 2301;
