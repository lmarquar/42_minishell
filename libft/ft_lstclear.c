/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:23:38 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:25:58 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
* Description
*	Deletes and frees the given element and every successor of that element,
*	using the function ’del’ and free(3).
*	Finally, the pointer to the list is set to NULL.
*
* Parameters
*	#1. The address of a pointer to tan element.
*	#2. The address of the function used to delete the content of the element.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		(del)(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
