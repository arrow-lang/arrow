// [ ] IR Source should be just a SPAN not the full AST node
// [ ] Parse/Build: Pointer Arithmetic
// [ ] Cast: Alias (pointer)
// [ ] Implicit cast to type alias from unnamed _literal_ of underlying type
// [x] If Expression
// [x] UNIT Type / Value
// [ ] DIVERGENT Type / Value
// [ ]   Global VS Local (Divergent Scope)
// [ ]   `break` and `continue` are considered divergent (block)
// [ ] Repeat: Break
// [ ] Repeat: Continue


// #[divergent]
def main(): int32 {
	let a = if false { 302; } else { return 4; };   // [ ] OK
	// let d = false or (return 20);                   // [x] OK
	// let d = (return 200) or true;                   // [x] OK
	// let d = false or true;                          // [x] OK
	// let b = (return 30) + 10;                       // [x] ERROR
  // let c = return 32;                              // [x] OK
 	// return c;                                       // [x] ERROR

	// [ ] OK
	// let counter = 0;
	// while counter < 10 {
	// 	counter = counter + if counter < 5 { 1; } else { break; };
	// 	counter = counter + if counter < 5 { 1; } else { continue; };
	// }

	let num = if false {
		320;
	} else {
		while true {
			break; // Divergent to the while loop but NOT the IF
		}
		while false {
			return 3; // Divergent to the while loop but NOT the IF
		}
	}

 	return 3;
}
