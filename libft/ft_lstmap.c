/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:35:40 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:45:02 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Iterates the list ’lst’ and applies the function ’f’ to the content of each
*	element. Creates a new list resulting of the successive applications of the
*	function ’f’. The ’del’ function is used to delete the content of an element
*	if needed. (e.g. if an allocation fails midway trough)
*
* Parameters
*	#1. The adress of a pointer to an element.
*	#2. The adress of the function used to iterate on the list.
*	#3. The adress of the function used to delete the content of an element if
*		needed.
*
* Return Values
*	The new list.
*	NULL if the allocation fails.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	t_list	*tmp;

	new = NULL;
	current = lst;
	while (current)
	{
		tmp = ft_lstnew((f)(current->content));
		if (tmp == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		current = current->next;
	}
	return (new);
}
