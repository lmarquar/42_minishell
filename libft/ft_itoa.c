/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:46:54 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:21:36 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_itoa(int n);

static size_t	count_digits(int n);
static void		rev_arr(char *s, size_t size);
static void		convert(char *s, int n, int sign);
static int		ft_abs(int n);

/*
* Description
*	Allocates (with malloc(3)) and returns a string representing the integer
*	received as an argument.
*	Negative numbers are handled.
*
* Return Values
*	The string representing the integer.
*	NULL if the allocation fails.
*/
char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	int		sign;

	len = count_digits(n);
	if (n < 0)
	{
		sign = -1;
		len++;
	}
	else
		sign = 1;
	s = (char *) malloc(sizeof (char) * (len + 1));
	if (s == NULL)
		return (NULL);
	convert(s, n, sign);
	rev_arr(s, len);
	s[len] = '\0';
	return (s);
}

static size_t	count_digits(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	rev_arr(char *s, size_t size)
{
	char	tmp;
	size_t	i;

	i = 0;
	while (i < size / 2)
	{
		tmp = s[i];
		s[i] = s[size - i - 1];
		s[size - i - 1] = tmp;
		i++;
	}	
}

static void	convert(char *s, int n, int sign)
{
	int	i;

	i = 0;
	if (n == 0)
		s[i] = '0';
	while (n != 0)
	{
		s[i++] = (ft_abs(n % 10)) + '0';
		n /= 10;
	}
	if (sign < 0)
		s[i++] = '-';
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
