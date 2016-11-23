import "std";

struct Box {
  value: int32;
}

implement Box {
  def new(value: int32): Box {
    let result: Box;
    result.value = value;

    return result;
  }

  def clone(self): Self {
    return Self.new(self.unwrap());
  }

  def unwrap(self): int32 {
    return self.value;
  }
}

def test_static() {
  let a = Box.new(10);
  let b = Box.new(a.value);
  let c = Box.new(32895);

  std.assert(a.value == 10);
  std.assert(b.value == 10);
  std.assert(c.value == 32895);
}

def test_instance_as_static() {
  let a = Box.new(3290);
  let b = Box.unwrap(a);
  a.value = 32495;
  let c = Box.clone(a);

  std.assert(b == 3290);
  std.assert(c.value == 32495);
}

def test_instance() {
  let a = Box.new(3290);
  let b = a.unwrap();
  a.value = 32495;
  let c = a.clone();

  std.assert(b == 3290);
  std.assert(c.value == 32495);
}

struct Pair<T, U> {
  first: T;
  second: U;
}

let a: int64 = 0;

implement<U, T> Pair<U, T> {
  def do() {
    a = 1;
  }
}

implement Pair<bool, int64> {
  def do() {
    a = 2;
  }
}

implement Pair<int64, bool> {
  def do() {
    a = 3;
  }
}

implement<T> Pair<T, T> {
  def do() {
    a = 4;
  }
}

implement<T> Pair<T, bool> {
  def do() {
    a = 5;
  }
}

def test_generic() {
  Pair<float64, float32>.do();
  std.assert(a == 1);

  Pair<bool, int64>.do();
  std.assert(a == 2);

  Pair<int64, bool>.do();
  std.assert(a == 3);

  Pair<float64, float64>.do();
  std.assert(a == 4);

  Pair<float64, bool>.do();
  std.assert(a == 5);
}

def main() {
  test_static();
  test_instance_as_static();
  test_instance();
  test_generic();
}
