// [ ] IR Source should be just a SPAN not the full AST node
// [ ] Parse/Build: Pointer Arithmetic
// [ ] Cast: Alias (pointer)
// [ ] Implicit cast to type alias from unnamed _literal_ of underlying type
// [x] If Expression
// [x] UNIT Type / Value
// [x] DIVERGENT Type / Value
// [ ] Repeat: Break
// [ ] Repeat: Continue
// [ ]   `break` and `continue` are considered divergent (block)

// #[divergent]
def main(): int32 {
	// [ ] OK
	// let counter = 0;
	// while counter < 10 {
	// 	counter = counter + if counter < 5 { 1; } else { break; };
	// 	counter = counter + if counter < 5 { 1; } else { continue; };
	// }

	// [ ] ?
	// let num = if false {
	// 	320;
	// } else {
	// 	while true {
	// 		break; // Divergent to the while loop but NOT the IF
	// 	}
	// 	while false {
	// 		return 3; // Divergent to the while loop but NOT the IF
	// 	}
	// }

 	return 3;
}
