
// Function Declaration

def methodA() {
}

def methodB(): int64 {
  return 40;
}

def methodC(): (int64, int64) -> int64 {
  return methodD;
}

def methodD(a: int64, b: int64): int64 {
  return methodB();
}

// Function Pointer/Object

// No-parameters; unit result
let a: () -> ();

// 2-parameters; bool result
let b: (int32, int64) -> bool;

// Takes 1 bool, returns a function that takes 1 int32, returns a function
// that takes a function that takes a bool; returns an int and then returns
// and int
let c: (bool) -> (int32) -> ((bool) -> int32) -> int32;
