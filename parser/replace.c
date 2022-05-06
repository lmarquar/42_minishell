/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:25:25 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/06 12:19:23 by chelmerd         ###   ########.fr       */
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
	while (str[j] && !is_ctrlchr(str[j]) && str[j] != '$' && !is_quote(str[j]))
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
	size_t	result_size;
	size_t	offset;

	printf("orignal:%s, word(start):%3s, word_len:%zu val:%s\n", str, word, word_len, val);
	if (!val)
		val = "";
	offset = 0;
	result_size = ft_strlen(str) + ft_strlen(val) + 1;
	result = ft_calloc(result_size, sizeof(char));
	offset = word - str;
	ft_strlcpy(result, str, offset + 1);
	printf("before:%s|\n", result);
	if (val[0])
	{
		printf("val not empty");
		ft_strlcat(result, val, result_size);
		offset += ft_strlen(val);
	}
	ft_strlcat(result, word + word_len + 1, result_size);
	free(str);
	return (result);
}

int	expand_env_vars(char **input, t_env_var *env_vars)
{
	char	*str;
	char	*val;
	size_t	key_len;
	size_t	i;
	int		single_qoute;

	str = *input;
	i = 0;
	single_qoute = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			val = find_val(str, i, &key_len, env_vars);
			if (key_len > 0)
			{
				str = replace_word(str, &str[i], key_len, val);
				if (val)
					i += ft_strlen(val) - 1;
			}
		}
		i++;
	}
	*input = str;
	printf("expanded:%s|\n", str);
	return (0);
}

void	expand_env_var(t_text_chunk *chunk, t_env_var *env_vars)
{
	char	*val;

	printf("key:%.*s", (int) (chunk->len - 1), chunk->str + 1);
	val = find_in_env(chunk->str + 1, chunk->len - 1, env_vars);
	if (!val)
		val = ft_strdup("");
	chunk->str = val;
	chunk->len = ft_strlen(val);
	printf("value of key:%s|\n", val);
}
