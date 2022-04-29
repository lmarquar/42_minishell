/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:46:10 by chelmerd          #+#    #+#             */
/*   Updated: 2022/02/21 12:39:31 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
* Description
*	Outputs the string ’s’ to the given file descriptor, followed by a newline.
*
* Parameters
*	#1. The string to output.
*	#2. The file descriptor on which to write.
*
* Return Values
*	the number of characters written
*/
int	ft_putendl_fd(const char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		count++;
		s++;
	}
	write(fd, "\n", 1);
	return (count + 1);
}
