/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:23:38 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/09 11:21:50 by chelmerd         ###   ########.fr       */
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
		if (del)
			(del)(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
