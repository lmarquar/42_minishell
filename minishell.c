/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:39:02 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/10 12:37:03 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signo)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	if (signo != 2)
		exit(0);
}

int	init_env(t_env_var **e_v)
{
	t_env_var	*var;

	(*e_v) = NULL;
	(*e_v) = malloc(sizeof(t_env_var));
	(*e_v)->key = "PATH";
	(*e_v)->val = getenv("PATH");
	var = malloc(sizeof(t_env_var));
	var->key = "PWD";
	var->val = getcwd(NULL, 0);
	(*e_v)->next = var;
	return (0);
}

// int	is_space(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\r'
// 		|| c == '\n' || c == '\v' || c == '\f')
// 		return (1);
// 	return (0);
// }

/*
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

char	*replace_word(char *str, char *key, char *val)
{
	char	*result;
	char	*start;
	size_t	offset;

	if (!val)
		val = "";
	offset = 0;
	result = ft_calloc((ft_strlen(str) + ft_strlen(val)), sizeof(char));

	start = ft_strnstr(str, key, ft_strlen(str));
	ft_strlcpy(result, str, (start - str) + 1);
	offset = start - str;
	ft_strlcpy(result + offset, val, ft_strlen(val) + 1);
	offset += ft_strlen(val);
	ft_strlcpy(result + offset, start + ft_strlen(key), ft_strlen(result));
	free(str);
	return (result);
}

int	expand_env_vars(char **input, t_env_var *env_vars)
{
	int		i;
	char	*mark;
	int		k;
	char	*var_key;
	char	*var_val;
	char	*needle;
	char	*in;

	in = *input;
	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
		{
			mark = &(in[i + 1]);
			k = 0;
			while (mark[k] && !is_space(mark[k]))
				k++;
			var_key = malloc(sizeof(char) * (k + 1));
			ft_strlcpy(var_key, mark, k + 1);
			var_val = find_in_env(var_key, env_vars);
			needle = ft_strjoin("$", var_key);
			in = replace_word(in, needle, var_val);
			free(needle);
			if (var_val)
				i = i + ft_strlen(var_val);
			else
				i--;
			free(var_key);
		}
		i++;
	}
	*input = in;
	return (0);
}
*/

int	init_bin(t_bin **bin, t_env_var *env_vars)
{
	*bin = ft_calloc(1, sizeof(t_bin));
	(*bin)->env = env_vars;
	return (0);
}

int	main(void)
{
	t_env_var	*env_vars;
	t_bin		*bin;
	t_cmd_line	cmd_line;

	// init env
	init_env(&env_vars);
	init_bin(&bin, env_vars);
	signal(SIGINT, &handle_signals);
	while (1)
	{
		bin->in = readline(SHELL_PROMT);
		if (!bin->in || !ft_strncmp(bin->in, "exit", 5))
		{
			// printf("exit");
			rl_replace_line("minishell>exit", 0);
			rl_redisplay();
			break ;
		}
		add_history(bin->in);
		// transform env_vars
		// check syntax
		// parse / analyse
		parse(bin->in, &cmd_line, env_vars, bin);
		// execute
		execute(bin);
		free(bin->in);
	}
	// clear list of env_vars

	return (0);
}
