#ifndef ATTR_H_
#define ATTR_H_

#ifdef __GNUC__
#define __always_inline __attribute__((always_inline))
#define __hot __attribute__((hot))
#define __cold __attribute__((cold))
#define __packed __attribute__((packed))
#define __fastcall __attribute__((fastcall))
#define __constructor __attribute__((constructor))
#define __destructor __attribute__((destructor))
#else
#error Unsupported compiler
#endif

#endif // ATTR_H_
