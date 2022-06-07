/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:03:45 by chelmerd          #+#    #+#             */
/*   Updated: 2022/06/07 16:11:13 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_var	*get_env_from_str(char *env_str)
{
	char		*key;
	size_t		key_size;
	char		*val;
	char		*val_ptr;

	if (env_str[0] == '=')
		return (NULL);
	val_ptr = ft_strnstr(env_str, "=", ft_strlen(env_str));
	if (!val_ptr)
		return (new_env_var(ft_strdup(env_str), NULL));
	val_ptr++;
	key_size = val_ptr - env_str;
	key = ft_calloc(key_size, sizeof (char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, key_size);
	val = ft_strdup(val_ptr);
	if (!val)
	{
		free(key);
		return (NULL);
	}
	return (new_env_var(key, val));
}
