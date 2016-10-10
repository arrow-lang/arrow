// [ ] IR Source should be just a SPAN not the full AST node
// [ ] Parse/Build: Pointer Arithmetic
// [ ] Cast: Alias (pointer)
// [ ] Implicit cast to type alias from unnamed _literal_ of underlying type
// [x] If Expression
// [x] UNIT Type / Value
// [ ] DIVERGENT Type / Value
// [ ] Repeat: Break
// [ ] Repeat: Continue

// #[divergent]
def main(): int32 {
	// let a = if false { 302; } else { return 4; };     // [ ] OK
	// let d = false or (return 20);                   // [ ] OK
	let d = (return 200) or true;                   // [ ] OK
	// let d = false or true;                   // [ ] OK
	// let b = (return 30) + 10;                       // [ ] ERROR
    // let c = return 32;                              // [x] OK
 	// return c;                                       // [x] ERROR
 	return 3;
}
