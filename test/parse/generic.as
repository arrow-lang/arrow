
// Declare: Generic Record
struct Box<T> { value: T; }
struct Point<T> { x: T; y: T; }
struct Pair<T, U> { first: T; second: U; }

// Declare: Generic Function
def method<T>(param: T): T {
  return param;
}

// Use: Generic Record
let a: Box<int32>;
let b: Pair<Box<int32>, Box<bool>>;

// Use: Generic Method
method<int64>(302);
method<Box<int32>>(a);
method<Pair<Box<int32>, Box<bool>>>(b);
