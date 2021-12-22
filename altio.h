/*  ALTIO.H
    C alternate standard library
    Standard Input/Output
*/

#if !defined(_ALTIO_H)
#define _ALTIO_H 1
#include "altarg.h"
#include "altdef.h"
#include "string.h"

int putchar(int c);

/* Screen input/output */

inline void print(const char* str, size_t size)
{
	for(size_t i = 0; i < size; i++) putchar(str[i]);
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);
    for(size_t i=0; i < strlen(format); i++) {
        if(format[i] == '%') {
			i++;
			if(format[i] == 'c') {
				char c = (char)va_arg(parameters, int);
				print(&c, sizeof(c));
			}
			else if(format[i] == 's') {
				const char* c = va_arg(parameters, const char*);
				print(c, strlen(c));
            }
            else if(format[i] == 'i') {
                const char* c = itoa(va_arg(parameters, int), 10);
                print(c, strlen(c));
            }
		}
		else putchar(format[i]);
    }
    va_end(parameters);
    return 1; /* STDIO compatability */
}

#endif // _ALTIO_H