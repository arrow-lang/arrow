
// Boolean
let b0 = false;
let b1;
b1 = b0;

if (b0 == b1) {
  // Do something
}

// Literal Integer/Real
let i0;
let f0;

i0 = 120;
f0 = 30.12;

let f1 = f0;
let i1 = i0;

// Conditional
let q;
let w;

if (false) {
  q = 30;
  w = 40;
} else {
  q = 3.12;
  w = 5.21;
}

methodF(q);

// type(q) = float32
// type(w) = float64

// Literal Integer + Real => Real
let m = 140;
m = 3.12;

// type(m) = float64

// Literal Integer w/Use
def methodI(param: int128) { }

let a = 30124;
methodI(a);

// Literal Integer w/Use
def methodF(param: float32) { }

let b = 320;
methodF(b);

// Function hoisting
let ab = methodG();

def methodG(): bool { return false; }
