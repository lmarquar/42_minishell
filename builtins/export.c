#include "builtins.h"
#include "../libft/libft.h"

static int	without_args(int fdout, char **arr)
{
	int	i;
	int	i2;

	i = -1;
	if (!arr)
		return (write(fdout, "no env_arr\n", 12));
	while (arr[++i] != NULL)
	{
		write(fdout, "declare -x ", 11);
		i2 = 0;
		while (arr[i][i2] != '=')
			write(fdout, &(arr[i][i2++]), 1);
		write(fdout, &(arr[i][i2++]), 1);
		write(fdout, "\"", 1);
		while (arr[i][i2])
			write(fdout, &(arr[i][i2++]), 1);
		write(fdout, "\"", 1);
		write(fdout, "\n", 1);
	}
	return (0);
}

static
int	is_valid_identifier_chr(int c, int pos)
{
	if (ft_isdigit(c) && pos == 0)
		return (0);
	else if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static
int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!is_valid_identifier_chr(s[i], i))
			return (0);
		i++;
	}
	return (1);
}

int	init_key_val(t_env_var *env, char *var_ass)
{
	int	i;
	int	i2;

	i = 0;
	while (var_ass[i] && var_ass[i] != '=')
		i++;
	env->key = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (var_ass[i] && var_ass[i] != '=')
	{
		env->key[i] = var_ass[i];
		i++;
	}
	env->val = NULL;
	if (!is_valid_identifier(env->key))
		return (1);
	i++;
	i2 = 0;
	while (var_ass[i + i2])
		i2++;
	env->val = ft_calloc(i2 + 1, sizeof(char));
	i2 = 0;
	while (var_ass[i + i2])
	{
		env->val[i2] = var_ass[i + i2];
		i2++;
	}
	return (0);
}

int	exec_export(int fdout, t_bin *bin, char *var_ass)
{
	t_env_var	*env;
	int			i;

	i = 0;
	if (!var_ass)
		without_args(fdout, bin->env_arr);
	else
	{
		while (var_ass[i] && var_ass[i] != '=')
			i++;
		if (!var_ass[i])
			return (1);
		env = bin->env;
		while (env->next)
			env = env->next;
		env->next = malloc(sizeof(t_env_var));
		if (init_key_val(env->next, var_ass) != 0)
		{
			clear_env_var(env->next);
			env->next = NULL;
			return (ft_error(1, "Identifier not valid"));
		}
		env->next->next = NULL;
	}
	return (0);
}