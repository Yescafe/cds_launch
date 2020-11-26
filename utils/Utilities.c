#include "./Utilities.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int _Error(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  int cnt = vfprintf(stderr, fmt, ap);
  va_end(ap);

  return cnt;
}

#ifdef NO_ASSERT
#  define _Assert(p, e) ((void) 0)
#else
  void _Assert(bool pred, const char* err_info)
  {
    if (!pred)
    {
      _Error("Assert failed! ");
      _Error(err_info);
      _Error("\n");
      exit(1);
    }
  }
#endif /* NO_ASSERT */

#ifdef __cplusplus
}
#endif /* __cplusplus */
