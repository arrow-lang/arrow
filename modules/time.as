import "libc";

// FIXME: Only works on macOS right now; arrow needs primitives for dealing with
//        platform differences. Only works on SAFARI (macOS 10.12). Needs
//        a whole lot of IFs.

/// A Duration represents the elapsed time between two points
/// as an int64 nanosecond count.
type Duration = int64;

/// Common durations.
///
/// To count the integral number of units in a duration, divide:
///   time.Now() / time.Second
///
/// To convert an integral number of units to a duration, multiply:
///   3 * time.Minute
let Nanosecond = Duration(1);
let Microsecond = Nanosecond * 1000;
let Millisecond = Microsecond * 1000;
let Second = Millisecond * 1000;
let Minute = Second * 60;
let Hour = Minute * 60;

implement Duration {
  /// Returns the duration as a floating point number of seconds.
  def Seconds(self): float64 {
    let s = self / Second;
    let ns = self % Second;

    return float64(s) + float64(ns) * 1e-9;
  }
}

/// A point in time.
struct Time {
  // Whole seconds (since the epoch: '0001-01-01T00:00:00')
  _sec: int64;

  // Nanoseconds (valid values are [0, 999999999])
  _nsec: int64;
}

implement Time {
  /// Returns the duration between two points in time.
  def Sub(self, u: Time): Duration {
    let d = 0;
    d += (self._sec - u._sec) * int64(Second);
    d += (self._nsec - u._nsec);

    // FIXME: Handle over/under-flow

    return Duration(d);
  }

  /// Returns the month in the year, in the range [1, 12].
  def Month(self): int8 {
    let d = self.YearDay();
    let m = d / 31;

    return int8(m);
  }

  /// Returns the day of the month, in the range [0, 365].
  def YearDay(self): int16 {
    let d = (self._sec / 86400);
    let y = 0;
    let n = 0;

    // Every 400 years there are a total of 97 days inserted (as leap days)
    // This brings the total days in a cycle to 146097

    // Account for the 400th year. The 400th year IS a leap year but the other
    // century years of a cycle are not.

    n = d / 146097;
    y = 400 * n;
    d -= 146097 * n;

    // There are 36524 days in a 100-year cycle (except for every 4th cycle
    // which has an extra day; this is why we removed the 400th year above)

    // Account for the century years

    n = d / 36524;
    n -= n >> 2;
    y += 100 * n;
    d -= 36524 * n;

    // Account for "normal" leap years (every 4th year)

    n = d / 1461;
    y += 4 * n;
    d -= 1461 * n;

    // Reduce the remaining days into years

    n = d / 365;
    n -= n >> 2;
    y += n;
    d -= 365 * n;

    return int16(d);
  }

  /// Returns the hour within the day, in the range [0, 23].
  def Hour(self): int8 {
    return int8((self._sec % 86400) / 3600);
  }

  /// Returns the minute offset within the hour, in the range [0, 59].
  def Minute(self): int8 {
    return int8((self._sec % 3600) / 60);
  }

  /// Returns the second offset within the minute, in the range [0, 59].
  def Second(self): int8 {
    return int8(self._sec % 60);
  }

  /// Returns the nanosecond offset within the second,
  /// in the range [0, 999999999].
  def Nanosecond(self): int64 {
    return self._nsec;
  }
}

/// Returns a `Time` representing the current point in time.
def Now(): Time {
  // FIXME: Handle failure
  let ts: libc.timespec;
  // FIXME: Macros are not exported by libc
  libc.clock_gettime(libc._CLOCK_REALTIME, &ts);

  // FIXME: Cleanup when we have record literals
  let t: Time;
  t._sec = ts.tv_sec;
  t._nsec = ts.tv_nsec;

  return t;
}

/// Returns a `Time` representing the current value of the clock.
def Monotonic(): Time {
  // FIXME: Handle failure
  let ts: libc.timespec;
  // FIXME: Macros are not exported by libc
  libc.clock_gettime(libc._CLOCK_MONOTONIC_RAW, &ts);

  // FIXME: Cleanup when we have record literals
  let t: Time;
  t._sec = ts.tv_sec;
  t._nsec = ts.tv_nsec;

  return t;
}
