/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:25:25 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/12 13:28:39 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/**
 * @brief replaces the $key with the value for the key
 *
 * @param chunk holds $key
 * @param env_vars list to find the value for the key
 */
void	expand_env_var(t_text_chunk *chunk, t_env_var *env_vars)
{
	char	*val;

	printf("key:%.*s", (int)(chunk->len - 1), chunk->str + 1);
	val = find_in_env(chunk->str + 1, chunk->len - 1, env_vars);
	if (!val)
		val = ft_strdup("");
	chunk->str = val;
	chunk->len = ft_strlen(val);
	printf("value of key:%s|\n", val);
}
