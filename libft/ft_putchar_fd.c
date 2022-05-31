/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:41:22 by chelmerd          #+#    #+#             */
/*   Updated: 2022/02/21 12:41:01 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
* Description
*	Outputs the character ’c’ to the given file descriptor.
*
* Parameters
*	#1. The character to output.
*	#2. The file descriptor on which to write.
*
* Return Values
*	the number of characters written (1)
*/
int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
