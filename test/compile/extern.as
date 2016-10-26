
// Type alias
type c_int = int32;

// Extern Let
extern let stderr: *int8;
extern let errno: c_int;

// Extern Function
extern "C" def exit(status: c_int);
extern def fprintf(stream: *int8, format: str, ...);

fprintf(stderr, "errno: %d\n", errno);
exit(-1);

// __stdcall method from windows.h (-lkernel32)
extern "stdcall" def Beep(frequency: int32, duration: int32): bool;

Beep(3, 3232);
