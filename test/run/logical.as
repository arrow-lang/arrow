extern "C" def printf(s: str, ...) -> int64;

let b0: bool = false;
let b1: bool = true;

let a: bool = b0 and b1;
let b: bool = b1 and b0;
let c: bool = b0 or b1;
let d: bool = b1 or b0;

printf("a = %b\n", a);
printf("b = %b\n", b);
printf("c = %b\n", c);
printf("d = %b\n", d);
