#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * _printf: coding printf function
 * @format: format string containing the characters and the specifiers
 * Return: formatted output string
 */

int _printf(const char *format, ...)
{
	const char *ptr;
	char *str;
	unsigned int i;

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
		switch(*ptr)
		{
			case 'c': i = va_arg(arg, int);
				  return(putchar(i));
				  break;
			case 's': str = va_arg(arg, char *);
				  return(puts(str));
				  break;
		}
	}
	va_end(arg);
	return (1);
}
