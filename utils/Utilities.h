#ifndef IVAN_UTILS_UTILITIES_H_
#define IVAN_UTILS_UTILITIES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdarg.h>      // variadic argument 
#include <stdio.h>       // vfprintf
#include <stdbool.h>     // bool
#include <stdlib.h>      // exit

int _Error(const char* fmt, ...);

#ifdef NO_ASSERT
#  define _Assert(p, e) ((void) 0)
#else
  void _Assert(bool pred, const char* err_info);
#endif /* STD_ASSERT */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_UTILS_UTILITIES_H_ */
