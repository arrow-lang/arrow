// 1. Tokenize (input => tokens)
// 2. Parse (tokens => AST)
// 3. Compile (AST => IR)
// 3.1 Compile: Build
// 4. Generate (IR => CODE [LLVM IR])
// 4.1 Generate: Declare
// 4.2 Generate: Define


// Compile:
let a: int16 = 10;
let b: bool = a;

middle::Declare
 // - Add all items

middle::TypeInfer
 // - Infer type via flow

middle::TypeCheck
 // - Check type (prevent type mismatch)

middle::Build
 // - Dive into the items and build their contents

middle::TypeDeduce

// Generator

back::Declare
 // - Add all items to LLVM

back::Build
 // - Generate each item's value

back::Type
 // - Make a LLVM type out of an IR type
