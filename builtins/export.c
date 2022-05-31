/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:57 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 11:09:46 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*next_smallest_string_uc(char **arr, char *s, char c)
{
	int		i;
	int		diff;
	char	*t;

	i = -1;
	while (arr[++i])
	{
		if (ft_strccmp(arr[i], s, '=') > 0)
			break ;
	}
	if (!arr[i])
		return (NULL);
	t = arr[i];
	i = -1;
	while (arr[++i])
	{
		diff = ft_strccmp(arr[i], t, c);
		if (diff < 0 && ft_strccmp(arr[i], s, c) > 0)
			t = arr[i];
	}
	return (t);
}

static
char	**ft_strsort(char **arr)
{
	int		i;
	int		k;
	char	**res;

	i = 0;
	while (arr[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	res[0] = next_smallest_string_uc(arr, "", '=');
	k = 1;
	while (k < i)
	{
		res[k] = next_smallest_string_uc(arr, res[k - 1], '=');
		k++;
	}
	return (res);
}

static
int	without_args_write(int fdout, char *s)
{
	int	i;

	write(fdout, "declare -x ", 11);
	i = 0;
	while (s[i] != '=' && s[i])
		write(fdout, &(s[i++]), 1);
	if (s[i])
	{
		write(fdout, &(s[i++]), 1);
		write(fdout, "\"", 1);
		while (s[i])
		{
			if (s[i] == '\"')
				write(fdout, "\\", 1);
			write(fdout, &(s[i++]), 1);
		}
		write(fdout, "\"", 1);
	}
	write(fdout, "\n", 1);
	return (0);
}

static
int	without_args(int fdout, char **arr)
{
	int		i;
	char	**arr_sorted;

	i = -1;
	if (!arr)
		return (write(fdout, "no env_arr\n", 12));
	arr_sorted = ft_strsort(arr);
	while (arr_sorted[++i] != NULL)
		without_args_write(fdout, arr_sorted[i]);
	free(arr_sorted);
	return (0);
}

int	exec_export(int fdout, t_bin *bin, char **args, int o_err_msg)
{
	t_env_var	*env_var;
	int			i;

	if (!*args)
		return (without_args(fdout, bin->env_arr));
	i = -1;
	while(args[++i])
	{
		env_var = get_env_from_str(args[i]);
		if (!env_var)
		{
			bin->exit_code = builtin_error(1, "export", "identifier is not valid");
			continue ;
		}
		if (o_err_msg)
		{
			clear_env_var(env_var);
			continue ;
		}
		if (find_in_env(env_var->key, ft_strlen(env_var->key), bin->env))
			bin->env = remove_env_var(bin->env, env_var->key);
		add_env_var(&bin->env, env_var);
	}
	return (0);
}
