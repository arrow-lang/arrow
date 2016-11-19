import "std";

let b0: bool = false;
let b1: bool = true;

let a: bool = b0 and b1;
let b: bool = b1 and b0;
let c: bool = b0 or b1;
let d: bool = b1 or b0;

std.assert(not a);
std.assert(not b);
std.assert(c);
std.assert(d);
