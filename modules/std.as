import "libc";

// Exit the program (with the given status)
def exit(status: int32) {
  libc.exit(libc.c_int(status));
}

// Check the condition and abort program execution if false
def assert(condition: bool) {
  if not condition {
    libc.abort();
  }
}

// Returns the size of a type in bytes
def size_of<T>(): uint64 {
  return (((0 as *T) + 1) as *uint8) - ((0 as *T) as *uint8);
}
