#ifndef EASYMOCK_VOIDFUNATTRFUN_H
#define EASYMOCK_VOIDFUNATTRFUN_H

#ifndef __printf
#define __printf(a,b)  __attribute__ ((format(printf,a ,b)))
#endif

#ifndef __section
#define __section(S) __attribute__ ((section(S)))
#endif

#ifndef __cold
#define __cold       __attribute__((cold))
#endif

#ifndef __multiAttr
#ifdef __clang__
#define __multiAttr __section("__DATA__,.multiAttr.text") __cold
#elif __GNUC__
#define __multiAttr __section(".multiAttr.text") __cold
#else
#error "Compiler not supported"
#endif
#endif

//Do not remove the extern as it actually test a bug fix.
extern __attribute__ ((format(printf,1 ,2))) void voidFunAttrFun(const char * fmt, ...);
extern __printf(2, 3) void voidFunAttrFunMacro(int a, const char * fmt, ...);
extern __attribute__ ((format(printf,1 ,2))) __attribute__((noinline)) void voidFunAttrFunAlwaysInline(const char * fmt, ...);
extern void __multiAttr voidFunAttrMultiAttr();

#define __noreturn __attribute__((__noreturn__))
extern __noreturn void voidFunNoReturn();

#if defined(__clang__) || defined(__llvm__)
#define __compiletime_error(message)
#elif defined(__GNUC__)
#define __compiletime_error(message) __attribute__((error(message)))
#endif
extern void __compiletime_error("copy source size is too small")
__bad_copy_from(void);

#endif //EASYMOCK_VOIDFUNATTRFUN_H
