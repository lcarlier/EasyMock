#ifndef EASYMOCK_VOIDFUNATTRFUN_H
#define EASYMOCK_VOIDFUNATTRFUN_H

#define __printf(a,b)  __attribute__ ((format(printf,a ,b)))

#define __section(S) __attribute__ ((section(#S)))
#define __cold       __attribute__((cold))
#define __multiAttr __section(.multiAttr.text) __cold

//Do not remove the extern as it actually test a bug fix.
extern __attribute__ ((format(printf,1 ,2))) void voidFunAttrFun(const char * fmt, ...);
extern __printf(2, 3) void voidFunAttrFunMacro(int a, const char * fmt, ...);
extern __attribute__ ((format(printf,1 ,2))) __attribute__((noinline)) void voidFunAttrFunAlwaysInline(const char * fmt, ...);
extern void __multiAttr voidFunAttrMultiAttr();

#endif //EASYMOCK_VOIDFUNATTRFUN_H
