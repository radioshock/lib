/*  STR.H
    C alternate standard library
    String handling
*/

#if !defined(_STRING_H)
#define _STRING_H 1

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len]) len++;
	return len;
}

/* Modified from wiki.osdev.org/Printing_To_Screen */
char* itoa(int value,int base)
{
    static char str[255];
    char *rc, *ptr, *low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

#endif // _STRING_H
