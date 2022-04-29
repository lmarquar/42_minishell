/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:01:31 by chelmerd          #+#    #+#             */
/*   Updated: 2022/02/21 12:37:45 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#define STDOUT 1

int				ft_printf(const char *format, ...);

static int		handle_token(char token, va_list ap);
static int		print_str(const char *s);
static int		print_hex(unsigned int n, int is_lowercase);
static int		print_long_hex(unsigned long n, int is_lowercase);

/*
* Description
*	Produces output acording to the given format and writes it to the stdout.
*
* Parameters
*	#1. the format string
*	... variable number of values to place in the format
*
* Return Values
*	the number of characters printed, or
*	a negative number if an error occurs.
*/
int	ft_printf(const char *format, ...)
{
	int		total_chars_printed;
	int		chars_printed;
	va_list	ap;

	total_chars_printed = 0;
	chars_printed = 0;
	va_start(ap, format);
	while (*format)
	{
		while (*format != '%' && *format)
		{
			total_chars_printed += ft_putchar_fd(*format, STDOUT);
			format++;
		}
		if (!*format)
			break ;
		format++;
		chars_printed = handle_token(*format, ap);
		if (chars_printed < 0)
			break ;
		total_chars_printed += chars_printed;
		format++;
	}
	va_end(ap);
	return (total_chars_printed);
}

static int	handle_token(char token, va_list ap)
{
	int		chars_printed;

	chars_printed = 0;
	if (token == 'c')
		chars_printed += ft_putchar_fd(va_arg(ap, int), STDOUT);
	else if (token == 's')
		chars_printed += print_str(va_arg(ap, char *));
	else if (token == 'p')
	{
		chars_printed += ft_putstr_fd("0x", STDOUT);
		chars_printed += print_long_hex(va_arg(ap, unsigned long), STDOUT);
	}
	else if (token == 'i' || token == 'd')
		chars_printed += ft_putnbr_fd(va_arg(ap, int), STDOUT);
	else if (token == 'u')
		chars_printed += ft_putnbr_fd(va_arg(ap, unsigned int), STDOUT);
	else if (token == 'x')
		chars_printed += print_hex(va_arg(ap, int), STDOUT);
	else if (token == 'X')
		chars_printed += print_hex(va_arg(ap, int), 0);
	else if (token == '%')
		chars_printed += ft_putchar_fd('%', STDOUT);
	else
		return (-1);
	return (chars_printed);
}

static int	print_str(const char *s)
{
	int	chars_printed;

	chars_printed = 0;
	if (!s)
		s = "(null)";
	chars_printed += ft_putstr_fd(s, STDOUT);
	return (chars_printed);
}

static int	print_hex(unsigned int n, int is_lowercase)
{
	int	chars_printed;
	int	offset;

	chars_printed = 0;
	offset = 'A';
	if (is_lowercase)
		offset = 'a';
	if (n < 10)
		chars_printed += ft_putnbr_fd(n, STDOUT);
	else if (n < 16)
		chars_printed += ft_putchar_fd(offset + (n - 10), STDOUT);
	else
	{
		chars_printed += print_hex(n / 16, is_lowercase);
		chars_printed += print_hex(n % 16, is_lowercase);
	}
	return (chars_printed);
}

static int	print_long_hex(unsigned long n, int is_lowercase)
{
	int	chars_printed;
	int	offset;

	chars_printed = 0;
	offset = 'A';
	if (is_lowercase)
		offset = 'a';
	if (n < 10)
		chars_printed += ft_putnbr_fd(n, STDOUT);
	else if (n < 16)
		chars_printed += ft_putchar_fd(offset + (n - 10), STDOUT);
	else
	{
		chars_printed += print_long_hex(n / 16, is_lowercase);
		chars_printed += print_long_hex(n % 16, is_lowercase);
	}
	return (chars_printed);
}
