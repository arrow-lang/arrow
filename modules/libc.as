// Includes all C headers for easier consumption by arrow modules

// C assert works by virtue of being a macro and cannot work directly in arrow
// TODO: Actual `assert` in arrow
// #include "assert.h"

// TODO: Complex types not currently supported by arrow
// #include "complex.h"

// Functions to determine the type contained in character data
#include "ctype.h"

// Reporting error conditions
#include "errno.h"

// Floating-point environment
#include "fenv.h"

// Limits of float types
#include "float.h"

// Format conversion of integer types
#include "inttypes.h"

// C alternative operator spellings would have no purpose here
// #include "iso646.h"

// Sizes of basic types
#include "limits.h"

// Localization utilities
#include "locale.h"

// Common mathematics functions
#include "math.h"

// Nonlocal jumps
#include "setjmp.h"

// Signal handling
#include "signal.h"

// C alignment macros would not work directly (being macros)
// #include "stdalign.h"

// C variable argument macros would not work directly (being macros)
// #include "stdarg.h"

// Atomic types
#include "stdatomic.h"

// C boolean type is not used anywhere in the C stdlib and has no place here
// #include "stdbool.h"

// Common definitions (ptrdiff_t and size_t are useful)
#include "stddef.h"

// Fixed-width integer types
#include "stdint.h"

// Input/output
#include "stdio.h"

// General utilities: memory management, program utilities, string conversions,
// random numbers
#include "stdlib.h"

// C noreturn function annotation wouldn't work directly
// #include "stdnoreturn.h"

// String (and memory) handling
#include "string.h"

// Type generic (magic) macros wouldn't work directly
// #include "tgmath.h"

// TODO: #if C11
// Thread library
// #include "thread.h"

// Time/date utilities
#include "time.h"

// TODO: #if C11
// UTF-16 and UTF-32 character utilities
// #include "uchar.h"

// Extended multibyte and wide character utilities
#include "wchar.h"

// Wide character classification and mapping utilities
#include "wctype.h"
