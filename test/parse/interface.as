interface Resource {
  def acquire(self) {
    // Do nothing (by default)
  }

  def release(self) {
    // Do nothing (by default)
  }
}

interface Sequence<T> {
  def size(self): uintx;
  def iter(self): Iterator<T>;
}

interface Box<T> {
  def get<U>(self): U;
}
