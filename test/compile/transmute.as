
// Transmute: <integer> to <pointer>
let a = 0 as *int8;

// Transmute: <pointer> to <pointer>
let b = 20;
let c = &b as *int128;

// Transmute: <pointer> to <integer>
let d = c as int64;
