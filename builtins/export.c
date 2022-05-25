#include "builtins.h"

static
int	without_args(int fdout, char **arr)
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
		{
			if (arr[i][i2] == '\"')
				write(fdout, "\\", 1);
			write(fdout, &(arr[i][i2++]), 1);
		}
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

int	exec_export(int fdout, t_bin *bin, char *var_ass, int o_err_msg)
{
	char		*val;
	t_env_var	*env_var;

	if (!var_ass)
		return (without_args(fdout, bin->env_arr));
	env_var = get_env_from_str(var_ass);
	if (!env_var)
	{
		perror("malloc error while init env var");
		return (1);
	}
	if (!is_valid_identifier(env_var->key))
		return (builtin_error(1, "export", "identifier is not valid"));
	if (o_err_msg)
	{
		clear_env_var(env_var);
		return (0);
	}
	val = find_in_env(env_var->key, ft_strlen(env_var->key), bin->env);
	if (val)
		bin->env = remove_env_var(bin->env, env_var->key);
	add_env_var(&bin->env, env_var);
	return (0);
}
