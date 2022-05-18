#include "builtins.h"

static int	without_args(int fdout, char **arr)
{
	int i;

	i = -1;
	while (arr[++i] != NULL)
	{
		write(fdout, "declare -x ", 11);
		write(fdout, arr[i], ft_strlen(arr[i]));
		write(fdout, "\n", 1);
	}
	return (0);
}

int	init_key_val(t_env_var *env, char *var_ass)
{
	int	i;
	int	i2;

	while (var_ass[i] && var_ass[i] != '=')
		i++;
	env->key = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (var_ass[i] && var_ass[i] != '=')
	{
		env->key[i] = var_ass[i];
		i++;
	}
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
	while (var_ass[i] && var_ass[i] != '=') i++;
	if (!var_ass[i])
		return (1);
	if (!var_ass[i + 1])
		return (1);
	env = bin->env;
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env_var));
	env = env->next;
	env->next = NULL;
	init_key_val(env, var_ass);
	return (0);
}