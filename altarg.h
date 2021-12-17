/*  ALTARG.H
    You should have recived a file named "LICENSE" (without quotes) with this software; if not, refer to https://opensource.org/licenses/MIT.
*/

#if !defined _ALTARG_H
#define _ALTARG_H 1

#if !defined(va_start)
#define va_start(v,l)        __builtin_va_start(v,l)
#endif // va_start

#if !defined(va_end)
#define va_end(v)        __builtin_va_end(v)
#endif // va_end

#if !defined(va_arg)
#define va_arg(v,l)        __builtin_va_arg(v,l)
#endif // va_arg

#if !defined(va_list)
#define va_list __builtin_va_list
#endif // va_list

#endif // _ALTARG_H