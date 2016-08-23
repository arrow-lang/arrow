
methodA(); // error

let mutable visited = a; // error "use before define"
let a = 40;
methodA(); // ok
visited = true;
methodA(); // ok

def methodA() {
  if (visited) {
    // [...]
  }
}

def methodB() {

}

// ast::Function

// ir::Function
// ir::Block {ir::Value}

// TODO
// [ ] Parenthetical grouping for expressions
// [ ] Type check ADD and ensure the operator "exists"
// [ ] Module initializer ".init" and execution with main
// [ ] Expression Statements
// [ ] Assignment
// [ ] Remaining expressions
