# Arrow
> Arrow is a fast (as or faster than C) general-purpose programming language.
> It does not employ a garbage collector and has minimal runtime overhead.

## 1. Introduction
This document is the primary reference for the Arrow programming language.

This document does not serve as an introduction to the language. Background
familiarity with the language is assumed.

## 3. Lexical Structure

### 3.1 Input format

An input file is interpreted as a sequence of Unicode code points encoded in
UTF-8. The text is normalized following [Unicode Normalization Form](http://unicode.org/reports/tr15/#Norm_Forms) KC (NFKC).

### 3.2 Identifiers

An identifier is a non-empty Unicode string strictly consisting of the
following character ranges:

###### Ranges of characters allowed

```
00A8, 00AA, 00AD, 00AF,
00B2-00B5, 00B7-00BA, 00BC-00BE, 00C0-00D6, 00D8-00F6, 00F8-00FF

0100-167F, 1681-180D, 180F-1FFF

200B-200D, 202A-202E, 203F-2040, 2054, 2060-206F

2070-218F, 2460-24FF, 2776-2793, 2C00-2DFF, 2E80-2FFF

3004-3007, 3021-302F, 3031-303F

3040-D7FF

F900-FD3D, FD40-FDCF, FDF0-FE44, FE47-FFFD

10000-1FFFD, 20000-2FFFD, 30000-3FFFD, 40000-4FFFD,
50000-5FFFD, 60000-6FFFD, 70000-7FFFD, 80000-8FFFD,
90000-9FFFD, A0000-AFFFD, B0000-BFFFD, C0000-CFFFD,
D0000-DFFFD, E0000-EFFFD
```

###### Ranges of characters disallowed initially

```
0300-036F, 1DC0-1DFF, 20D0-20FF, FE20-FE2F
```

### 3.3 Comments

Comments strictly serve as program documentation and are stripped on
compilation.

1. _Line comments_ start with the character sequence `//` and stop at the end of the line.1.

2. _Block comments_ start with the character sequence `/*` and stop at the corresponding `*/`. Unlike C, block comments may be nested within each other.

### 3.4 Whitespace
Whitespace is any non-empty string containing only of the following characters:

| Character | Description                  |
|-----------|------------------------------|
| `U+0020`  | Space                        |
| `U+0009`  | Tab                          |
| `U+000a`  | New Line                     |
| `U+000d`  | Carriage Return              |
| `U+000b`  | Line Tabulation              |
| `U+000c`  | Form Feed                    |
| `U+001c`  | File Separator               |
| `U+001d`  | Group Separator              |
| `U+001e`  | Record Separator             |
| `U+0085`  | Next Line (C1 Control Code)  |
| `U+2028`  | Line Separator               |
| `U+2029`  | Paragraph Separator          |

### 3.5 Keywords

The following are keywords and may not be used as identifiers:

```
_
and
as
break
continue
else
extern
false
global
if
let def
loop
mutable
not
or
return
struct
true
unless
until
while
```

### 3.6 Punctuators

The following character sequences represent operators,
delimiters, and other special tokens:

```
+
-
/
*
%
&
|
^
!
=
<
>
.
:
;
{
}
(
)
[
]
,

+=
-=
*=
/=
%=
&=
|=
^=
==
!=
>=
<=
```

### 3.7 Literals

#### 3.7.1 Number literals

The type of a number literal is determined by type inference:

  - If an integer type can be uniquely determined from the
    surrounding program context, the integer literal has that type.

  - If the program context infers a type too small for the literal,
    it is considered a static type error.

##### 3.7.1.1 Integer literals

An _integer literal_ has one of four forms:

 - A _decimal literal_ starts with a decimal digit and continues with
   any mixture of decimal digits and underscores.

 - A _hex literal_ starts with the character sequence `U+0030` `U+0078` (`0x`)
   and continues as any mixture of hex digits and underscores.

 - An _octal literal_ starts with the character
   sequence `U+0030` `U+006F` (`0o`)
   and continues as any mixture of octal digits and underscores.

 - A _binary literal_ starts with the character
   sequence `U+0030` `U+0062` (`0b`)
   and continues as any mixture of binary digits and underscores.

##### 3.7.1.2 Floating-point literals

A _floating-point literal_ has one of two forms:

 - A _decimal literal_ followed by a period character `U+002E` (`.`).
  This is optionally followed by another _decimal literal_, with an
  optional _exponent_.

 - A single _decimal literal_ followed by an _exponent_.

#### 3.7.2 Boolean literals

The two values of the boolean type are: `true` and `false`.
