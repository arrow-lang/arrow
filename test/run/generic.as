import "std";

def test_size() {
  std.assert(std.size_of<bool>() == 1);
  std.assert(std.size_of<int64>() == 8);
  std.assert(std.size_of<int128>() == 16);

  struct Box<T> {
    value: T;
  }

  std.assert(std.size_of<Box<int128>>() == 16);

  struct Pair<T, U> {
    first: T;
    second: U;
  }

  std.assert(std.size_of<Pair<Box<int128>, int64>>() == 24);
}

def main() {
  test_size();
}
