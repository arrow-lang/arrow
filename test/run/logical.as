extern def printf(s: str, ...);

let b0: bool = false;
let b1: bool = true;

let a: bool = b0 and b1;
let b: bool = b1 and b0;
let c: bool = b0 or b1;
let d: bool = b1 or b0;

printf("a = %d\n", a);
printf("b = %d\n", b);
printf("c = %d\n", c);
printf("d = %d\n", d);
