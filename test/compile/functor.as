def methodA() {
}

def methodB(): () -> () {
  return methodA;
}

let ptr_a = methodA;
ptr_a();

let ptr_a_2 = ptr_a;
ptr_a_2();

let ptr_b = methodB;
ptr_b();
let ptr_a_b = methodB();
ptr_a_b();
methodB()();

def methodC(a: () -> ()) {
  a();
}

methodC(methodB());
