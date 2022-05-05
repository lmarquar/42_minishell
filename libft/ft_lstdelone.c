/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:17:59 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 10:29:01 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
* Description
*	Takes as a parameter an element and frees the memory of the element’s
*	content using the function ’del’ given as a parameter and free the element.
*	The memory of ’next’ is not be freed.
*
* Parameters
*	#1. The address of a pointer to an element.
*	#2. The address of the function used to delete the content of the element.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	(del)(lst->content);
	free(lst);
}
