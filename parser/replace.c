/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:25:25 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/04 15:26:37 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_in_env(char *key, size_t key_len, t_env_var *env_vars)
{
	while (env_vars && ft_strncmp(env_vars->key, key, key_len) != 0)
	{
		env_vars = env_vars->next;
	}
	if (env_vars)
		return (env_vars->val);
	return (NULL);
}

char	*find_val(char *str, size_t i, size_t *key_len, t_env_var *env_vars)
{
	char	*val;
	size_t	j;

	i++;
	j = i;
	while (str[j] && !is_ctrlchr(str[j]))
	{
		j++;
	}
	*key_len = j - i;
	val = find_in_env(&str[i], *key_len, env_vars);
	return (val);
}

char	*replace_word(char *str, char *word, size_t word_len, char *val)
{
	char	*result;
	size_t	offset;

	if (!val)
		val = "";
	offset = 0;
	result = ft_calloc((ft_strlen(str) + ft_strlen(val) + 1), sizeof(char));
	offset = word - str;
	ft_strlcpy(result, str, offset + 1);
	if (val[0])
	{
		ft_strlcpy(result + offset, val, ft_strlen(val) + 1);
		offset += ft_strlen(val);
	}
	ft_strlcpy(result + offset, str + word_len + 1, ft_strlen(result));
	free(str);
	return (result);
}

int	expand_env_vars(char **input, t_env_var *env_vars)
{
	char	*str;
	char	*val;
	size_t	key_len;
	size_t	i;

	str = *input;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			val = find_val(str, i, &key_len, env_vars);
			if (key_len > 0)
			{
				str = replace_word(str, &str[i], key_len, val);
				i += key_len;
			}
		}
		i++;
	}
	*input = str;
	return (0);
}
