// Statement (Expression)
if condition {
  // [...]
} else if other_condition {
  // [...]
} else {
  // [...]
}

if condition {
  // [...]
}

// Expression (will look a lot nicer once `;` is optional)
let name: int32 = if a > b {
  30;
} else {
  0xdeadbeef;
};
