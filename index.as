// [ ] IR Source should be just a SPAN not the full AST node
// [ ] Parse/Build: Pointer Arithmetic
// [ ] Cast: Alias (pointer)
// [ ] Implicit cast to type alias from unnamed _literal_ of underlying type
// [x] If Expression
// [x] UNIT Type / Value
// [ ] DIVERGENT Type / Value
// [ ] Repeat: Break
// [ ] Repeat: Continue

def main(): int32 {
	// let a = if false { 302; } else { return; };     // [ ] OK
	// let b = (return 30) + 10;                       // [ ] ERROR
 	let c = return 32;                              // [ ] OK
 	// return c;                                       // [x] ERROR
}
