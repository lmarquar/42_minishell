/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:18:44 by chelmerd          #+#    #+#             */
/*   Updated: 2022/02/07 13:26:50 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	prints an Error to the standard error (fd = 2)
*	Example: "Error\n This is an error msg (Error Code: 41)\n"
*
* Parameters
*	#1. the error code
*	#2. an descriptive error message
*
* Return Values
*	the error code
*/
int	ft_error(int error, char *msg)
{
	int	fd;

	fd = 2;
	ft_putendl_fd("Error", fd);
	if (ft_strlen(msg) > 0)
	{
		ft_putstr_fd(msg, fd);
		ft_putstr_fd(" (Error Code: ", fd);
		ft_putnbr_fd(error, fd);
		ft_putendl_fd(")", fd);
	}
	return (error);
}
