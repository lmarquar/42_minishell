#include "execute.h"

//delete this
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (1);
	return (0);
}
//delete until here

char	*get_full_path(char *cd, char *gd)
{
	int		i;
	char	*res;
	char	*tmp;

	res = ft_strjoin(cd, gd);
	i = 0;
	while (res[i])
		i++;
	if (res[--i] != '/')
	{
		tmp = res;
		res = ft_strjoin(res, "/");
		free(tmp);
	}
	free(cd);
	return (res);
}


int	exec_cd(int inout[], char *dir_raw)
{
	int		i;
	char	*curdir;
	char	*dir;
	char	*error_msg;

	curdir = getcwd(NULL, 0);
	curdir = ft_strjoin(curdir, "/");
	if (dir_raw[0] != '/')
		dir = get_full_path(curdir, dir_raw);
	i = chdir(dir);
	error_msg = ft_strjoin("minishell: cd: ", dir_raw);
	if (i == -1)
		perror(error_msg);
	inout[0]++;
	inout[1]++;
	free(error_msg);
	free(curdir);
	free(dir);
	return (0);
}

int	exec_echo(int inout[], char **args)
{
	int		i;

	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], inout[1]);
		i++;
	}
	if (!ft_strncmp(args[1], "-n", 2))
		write(inout[1], "\n", 1);
	inout[0]++;
	inout[1]++;
	return (0);
}

//by far not really good. f.ex.: "" are missing
int	exec_export(int inout[], t_bin *bin, char *var_ass)
{
	t_env_var	*env;
	int			i;
	int			i2;

	i = 0;
	if (!var_ass)
	{
		while (bin->env_arr[i] != NULL)
			printf("declare -x %s\n", bin->env_arr[i++]);
		return (0);
	}
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
	inout[0]++;
	inout[1]++;
	return (0);
}


int	exec_builtin(t_bin *bin, char **args, int fdin, int fdout)
{
	int	inout[2];

	inout[0] = fdin;
	inout[1] = fdout;
	if (ft_strcmp(args[0], "echo"))
		exec_echo(inout, args);
	if (ft_strcmp(args[0], "cd"))
		exec_cd(inout, args[1]);
	if (ft_strcmp(args[0], "export"))
		exec_export(inout, bin, args[1]);
	return (0);
}
