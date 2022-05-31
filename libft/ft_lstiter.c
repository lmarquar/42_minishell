/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:28:24 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:30:52 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Iterates the list ’lst’ and applies the function ’f’ to the content of each
*	element.
*
* Parameters
*	#1. The address of a pointer to an element.
*	#2. The adress of the function used to iterate on the list.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current)
	{
		(f)(current->content);
		current = current->next;
	}
}
