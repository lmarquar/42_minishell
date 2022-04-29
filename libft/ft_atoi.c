/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:42 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:11:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi(const char *s);

static int	value(const char *s);
static int	is_space(int c);

/*
* Description
*	Converts the string into an integer representation.
*
*	The string may begin with an arbitrary amount of white space (as determined
*	by isspace) followed by a single optional `+' or `-' sign. It is assumed
*	that the number is in base 10. The conversion stops at the first character
*	that is not a valid digit.
*
* Return Values
*	the resulting int from the conversion
*/
int	ft_atoi(const char *s)
{
	int	sign;

	sign = 0;
	while (is_space(*s))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
	{
		sign = 1;
		s++;
	}
	else
		sign = 1;
	return (sign * value(s));
}

static int	value(const char *s)
{
	int	result;

	result = 0;
	while (*s && '0' <= *s && *s <= '9')
	{
		result *= 10;
		result += *s - '0';
		s++;
	}
	return (result);
}

static int	is_space(int c)
{
	char	chr;

	chr = (char) c;
	if (chr == '\t' || chr == '\n' || chr == '\v'
		|| chr == '\f' || chr == '\r' || chr == ' ')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
