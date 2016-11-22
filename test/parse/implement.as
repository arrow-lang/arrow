import "./interface";

struct Cell {
  value: str;
}

struct Box<T> {
  value: T;
}

struct Pair<T, U> {
  first: T;
  second: U;
}

implement Cell {
  def row(): Row {
    // [...]
  }
}

implement<T> Box<T> {
  def unwrap(self): T {
    return self.value;
  }
}

implement Pair<bool, Box<bool>> {
  // [...]
}

implement<T, U> Sequence<T> for Box<U> {
  // [...]
}

implement<T> Resource for Box<T> {
  def release(self) {
    // [...]
  }
}
