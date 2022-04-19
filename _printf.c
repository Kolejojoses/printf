#include "main.h"

int _printf(const char *format, ...)
{
	const char *ptr;
	unsigned int i;
	char *str;

	va_list arg;
	va_start(arg, format);

	for (ptr = format; *ptr != '\0'; ptr++)
	{
		while (*ptr != '%')
		{
			putchar(*ptr);
			ptr++;
		}
		ptr++;
		switch (*ptr)
		{
			case 'c': i = va_arg(arg, int);
				return (putchar(i));
				break;
			case 's': str = va_arg(arg, char *);
				return(puts(str));
			default:
				break;
		}
	}
	va_end(arg);
}