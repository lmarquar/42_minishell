/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:25:25 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/24 23:29:40 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// chunk->expand is set to two to indicate it has to be freed
int	replace_question_mark(t_text_chunk *chunk, int exit_code)
{
	char	*code;

	code = ft_itoa(exit_code);
	if (!code)
	{
		perror("ft_itoa malloc");
		chunk->len = 0;
		chunk->expand = 0;
		return (1);
	}
	chunk->str = code;
	chunk->len = ft_strlen(chunk->str);
	chunk->expand = 2;
	return (0);
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

	// printf("key:%.*s", (int)(chunk->len - 1), chunk->str + 1); // debug
	val = find_in_env(chunk->str + 1, chunk->len - 1, env_vars);
	if (!val)
		val = "";
	chunk->str = val;
	chunk->len = ft_strlen(val);
	// printf("value of key:%s|\n", val); // debug
}

int		expand_wildcard_bonus(t_list *chunks)
{
	char	**arr;
	t_list	*tmp;
	int		i;

	arr = replace_ast_bonus(((t_text_chunk *)chunks->content)->str);
	if (!arr)
		return (0);
	free(((t_text_chunk *)chunks->content)->str);
	((t_text_chunk *)chunks->content)->str = arr[0];
	i = 0;
	while (arr[++i])
	{
		tmp = chunks->next;
		chunks->next = ft_calloc(1, sizeof(t_list));
		chunks = chunks->next;
		chunks->content = ft_calloc(1, sizeof(t_text_chunk));
		((t_text_chunk *)chunks->content)->str = arr[i];
		chunks->next = tmp;
	}
	return (0);
}

/**
 * @brief replace the text in a chunk if needed
 *
 * @param chunks linked list of t_text_chunks
 * @param env linked list of enviroment variables
 * @param exit_code the last exit code in the shell
 */
void	expansion(t_list *chunks, t_env_var *env, int exit_code)
{
	t_text_chunk	*chunk;

	while (chunks)
	{
		chunk = (t_text_chunk *) chunks->content;
		if (!chunk->expand)
		{
			chunks = chunks->next;
			continue ;
		}
		if (chunk->len == 1)
			chunk->expand = 0;
		else if (chunk->len == 2 && chunk->str[1] == '?')
		{
			if (replace_question_mark(chunk, exit_code) != 0)
				break ; //TODO: handle error
		}
//		else if (ft_strchr(chunk->str, '*'))
//			expand_wildcard_bonus(chunks);
		else
			expand_env_var(chunk, env);
		chunks = chunks->next;
	}
}
