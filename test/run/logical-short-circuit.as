import "std";

let counter = 0;

if false or { counter = counter + 1; true; } {
  std.assert(true);
}

if true or { counter = counter + 1; false; } {
  std.assert(true);
}

if false and { counter = counter + 1; true; } {
  std.assert(false);
}

if true and { counter = counter + 1; true; } {
  std.assert(true);
}

std.assert(counter == 2);
