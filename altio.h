/*  ALTIO.H
    C alternate standard library
    Standard Input/Output
*/

#if !defined(_ALTIO_H)
#define _ALTIO_H 1

#if defined(__unix__) || defined(__APPLE__)
#include "unistd.h"
#elif defined(_WIN32)
#error "altio.h: Microsoft Windows is not supported at this time."
#endif // __unix__ __APPLE__ _WIN32
#include "altarg.h"
#include "altdef.h"
#include "string.h"

#define _alterr 2
#define _altout 1
#define _altin 0

int putchar(int c) {
    char out = c;
    write(_altout, &out, sizeof(out));
    return 1;
}

// Screen input/output

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
    return 1;
}

#endif // _ALTIO_H