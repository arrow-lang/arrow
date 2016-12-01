// TODO: move to std/vector.as (once we have directory import)
import "std";
import "libc";

struct Vector<T> {
  // TODO: `uintx`
  capacity: uint64;

  // TODO: `uintx`
  size: uint64;
  data: *T;
}

implement<T> Vector<T> {
  def New(): Self {
    // TODO: Replace with `return Vector<T>{};`
    let v: Vector<T>;
    v.data = std.null<T>();
    v.size = 0;
    v.capacity = 0;

    return v;
  }

  def Release(self) {
    if self.data != std.null<T>() {
      libc.free(self.data as *uint8);
      self.data = std.null<T>();
    }
  }

  // TODO: `uintx`
  def Reserve(self, capacity: uint64) {
    // Check existing capacity
    if capacity <= self.capacity { return; }

    // Ensure that we allocate in chunks of <CHUNK>
    // FIXME: Requesting 10, allocates 20
    self.capacity = capacity + (10 - (capacity % 10));

    // Reallocate memory
    self.data = libc.realloc(
      self.data as *uint8, self.capacity * std.size_of<T>()) as *T;
  }

  def Push(self, element: T) {
    // Request additional memory (if needed)
    self.Reserve(self.capacity + 1);

    // Move element into the container
    // BUG(arrow): I think the reason why memcpy doesn't work is the same
    //             reason you can't take the address of a by-ref struct
    *(self.data + self.size) = element;
    // libc.memcpy((self.data + self.size) as *uint8, &element as *uint8,
    //   std.size_of<T>());

    // Increment size to keep track of element insertion
    self.size += 1;
  }

  // TODO: `uintx`
  def Get(self, index: uint64): T {
    // TODO: Assertion index < size
    return *(self.data + index);
  }

  // TODO: `uintx`
  def Set(self, index: uint64, element: T): T {
    // TODO: Assertion index < size
    *(self.data + index) = element;
  }
}
