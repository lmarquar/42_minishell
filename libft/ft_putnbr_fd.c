/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:47:55 by chelmerd          #+#    #+#             */
/*   Updated: 2022/02/21 12:40:11 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int			ft_putnbr_fd(long n, int fd);

static int	putnbr(long n, int fd);
static int	ft_abs(int n);

/*
* Description
*	Outputs the integer ’n’ to the given file descriptor.
*
* Parameters
*	#1. The integer to output.
*	#2. The file descriptor on which to write.
*
* Return Values
*	the number of characters written
*/
int	ft_putnbr_fd(long n, int fd)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			count++;
		}
		count += putnbr(n, fd);
	}
	return (count);
}

/*
* Description
*	Recursivly calls itself to write digit by digit to the given file descriptor.
*/
static int	putnbr(long n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n != 0)
	{
		if (n > 9 || n < -9)
			count += putnbr(n / 10, fd);
		c = ft_abs(n % 10) + '0';
		write(fd, &c, 1);
		return (count + 1);
	}
	return (0);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
