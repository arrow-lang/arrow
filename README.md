# Arrow
> Arrow is a fast (as or faster than C) general-purpose programming language. It does not employ a garbage collector and has minimal runtime overhead.

## Build

### Packages

#### Linux — Ubuntu

  - git
  - libncurses-dev
  - libz-dev
  - libgmp-dev
  - libffi-dev
  - https://github.com/fmtlib/fmt — Will eventually vendor or replace this
  - libboost-all-dev
  - llvm-3.8-dev
  - libclang-3.8-dev

### Clone

```sh
$ git clone https://github.com/arrow-lang/arrow.git
$ cd arrow
$ git submodule update --init
```

### Configure

```sh
$ ./waf configure --with-llvm-config=`which llvm-config-3.8` --release
```

### Build

```sh
$ ./waf
```

### Install

```sh
$ sudo ./waf install
```
