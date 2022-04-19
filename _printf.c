#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _printf: coding printf function
 * @format: format string containing the characters and the specifiers
 * Return: formatted output string
 */

int ft_putchar(int c) {
    char a[1];
    a[0] = (char)c;
    return write(0, a, 1);
}

static int ft_printf_aux(const char *fmt, va_list ap, int len);

static int ft_print_c(const char *fmt, va_list ap, int len) {
    int c = va_arg(ap, int);
    ft_putchar(c);
    return ft_printf_aux(fmt, ap, len + 1);
}

static int ft_putnum(unsigned long long n, unsigned int base, const char *digits) {
    int res = 1;
    if (n >= base)
        res += ft_putnum(n / base, base, digits);
    ft_putchar(digits[n % base]);
    return res;
}

static int ft_print_d(const char *fmt, va_list ap, int len) {
    int n = va_arg(ap, int);
    unsigned long long u;
    if (n < 0) {
        ft_putchar('-');
        len++;
        u = -(unsigned)n;
    } else {
        u = n;
    }
    len += ft_putnum(u, 10, "0123456789");
    return ft_printf_aux(fmt, ap, len);
}

static int ft_print_o(const char *fmt, va_list ap, int len) {
    unsigned int n = va_arg(ap, unsigned int);
    len += ft_putnum(n, 8, "01234567");
    return ft_printf_aux(fmt, ap, len);
}

static int ft_print_u(const char *fmt, va_list ap, int len) {
    unsigned int n = va_arg(ap, unsigned int);
    len += ft_putnum(n, 10, "0123456789");
    return ft_printf_aux(fmt, ap, len);
}

static int ft_print_x(const char *fmt, va_list ap, int len) {
    unsigned int n = va_arg(ap, unsigned int);
    len += ft_putnum(n, 16, "0123456789abcdef");
    return ft_printf_aux(fmt, ap, len);
}

static int ft_print_X(const char *fmt, va_list ap, int len) {
    unsigned int n = va_arg(ap, unsigned int);
    len += ft_putnum(n, 16, "0123456789ABCDEF");
    return ft_printf_aux(fmt, ap, len);
}

static int ft_print_s(const char *fmt, va_list ap, int len) {
    const char *s = va_arg(ap, const char *);
    if (s == NULL) {
        s = "(null)";
    }
    while (*s) {
        ft_putchar(*s++);
        len++;
    }
    return ft_printf_aux(fmt, ap, len);
}

typedef int (*ft_print_dispatch_f)(const char *fmt, va_list ap, int len);

static ft_print_dispatch_f const ft_print_dispatch[256] = {
    ['c'] = ft_print_c,
    ['d'] = ft_print_d,
    ['i'] = ft_print_d,
    ['o'] = ft_print_o,
    ['u'] = ft_print_u,
    ['x'] = ft_print_x,
    ['X'] = ft_print_X,
    ['s'] = ft_print_s,
};

static int ft_printf_aux(const char *fmt, va_list ap, int len) {
    int c;

    while (*fmt) {
        c = (unsigned char)*fmt++;
        if (c != '%') {
            ft_putchar(c);
            len++;
        } else {
            c = (unsigned char)*fmt++;
            if (ft_print_dispatch[c] == NULL) {
                if (c == '\0')
                    break;
                ft_putchar(c);
                len++;
            } else {
                return ft_print_dispatch[c](fmt, ap, len);
            }
        }
    }
    return len;
}

int ft_vprintf(const char *fmt, va_list ap) {
    return ft_printf_aux(fmt, ap, 0);
}

int ft_printf(const char *fmt, ...) {
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = ft_printf_aux(fmt, ap, 0);
    va_end(ap);
    return n;
}