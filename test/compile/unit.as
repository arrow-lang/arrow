
def methodA() {
  return; 
}

def methodB() {
  return methodA();
}

def methodC(): () {
  return methodB();	
}

def methodD() {
  let var: () = methodC();
  return var;
}

def methodE() {
  let var;
  var = methodD();
  return var;
}

def methodF() {
  let var = ();
  return var;
}

def methodG() {
  return ();
}

def methodH(param: ()) {
  return methodH(methodE());
}

def main() {
  methodH(());
}

main();