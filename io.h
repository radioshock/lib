/*  IO.H
	C alternate standard library
	Standard Input/Output
*/

#if !defined(_ALTIO_H)
#define _ALTIO_H 1

#if defined(__unix__) || defined(__APPLE__)
#include "unistd.h"
#else
#error "altio.h: Non-unix environments are currently unsupported."
#endif // __unix__ __APPLE__

#include "altarg.h"
#include "altdef.h"
#include "altstr.h"

#define _alterr 2
#define _altout 1
#define _altin 0

// Screen input/output

int putchar(int c) {
	char out = c;
	write(_altout, &out, sizeof(out));
	return 1;
}

#define print(c,s) for(size_t i = 0; i < (size_t)s; i++) putchar( ((const char*)c) [i]);

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

// Keyboard Input/Output

const char* scan() {
	static char in[255];
	read(_altin, in, 255);
	return in;
}

int getchar(void) {
	const char* in;
	in = scan();
	return in[0];
}

int scanf(const char* format, ...) {
	va_list parameters;
	va_start(parameters, format);
	for(size_t i=0; i < strlen(format); i++) {
		if(format[i] == '%') {
			i++;
			if(format[i] == 'c') {
				char* buffer = va_arg(parameters, char*);
				char c = getchar();
				*buffer = c;
			}
			else if(format[i] == 's') {
				char** buffer = va_arg(parameters, char**);
				char* c = (char*)scan();
				*buffer = c;
			}
		}
	}
	va_end(parameters);
	return 1;
}

#endif // _ALTIO_H
