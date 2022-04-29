/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:02:59 by chelmerd          #+#    #+#             */
/*   Updated: 2021/12/09 15:27:00 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Counts the number of elements in a list.
*
* Parameters
*	#1. The beginning of the list.
*
* Return Values
*	Length of the list.
*/
int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current;

	size = 0;
	if (lst == NULL)
		return (0);
	current = lst;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
