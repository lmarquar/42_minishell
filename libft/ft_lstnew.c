/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:45:07 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:47:46 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Description
*	Allocates (with malloc(3)) and returns a new element. The variable ’content’
*	is initialized with the value of the parameter ’content’. 
*	The variable ’next’ is initialized to NULL.
*
* Parameters
*	#1. The content to create the new element with.
*
* Return Values
*	The new element.
*	NULL if the allocation fails.
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof (t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
