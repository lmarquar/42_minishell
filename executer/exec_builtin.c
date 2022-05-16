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

int	exec_echo(int fdout, char **args)
{
	int	i;

	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
		i++;
	while (args[i])
	{
		write(fdout, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(args[1], "-n", 2))
		write(1, "\n", 1);
	return (0);
}

//by far not really good. f.ex.: "" are missing
int	exec_export(int fdout, t_bin *bin, char *var_ass)
{
	t_env_var	*env;
	int			i;
	int			i2;
	
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) < 0)
			return (handle_dup2error());
		close(fdout);
	}
	i = 0;
	if (!var_ass)
	{
		while (bin->env_arr[i] != NULL)
			printf("declare -x %s\n", bin->env_arr[i++]);
		return (0);
	}
	while (var_ass[i] && var_ass[i] != '=')
		i++;
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
	return (0);
}

int	exec_cd(char *dir)
{
	int		i;
	char	*curdir;

	curdir = getcwd(NULL, 0);
	curdir = ft_strjoin(curdir, "/");
	if (dir[0] != '/')
		dir = get_full_path(curdir, dir);
	i = chdir(dir);
	if (i == -1)
		perror("chdir failed");
	return (0);
}

int	exec_pwd(int fdout)
{
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) < 0)
			return (handle_dup2error());
		close(fdout);
	}
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	exec_builtin(t_bin *bin, char **args, int fdin, int fdout)
{
	int	inout[2];

	inout[0] = fdin;
	inout[1] = fdout;
	if (ft_strcmp(args[0], "echo"))
		bin->exit_code = exec_echo(inout[1], args);
	if (ft_strcmp(args[0], "cd"))
		bin->exit_code = exec_cd(args[1]);
	if (ft_strcmp(args[0], "export"))
		bin->exit_code = exec_export(inout[1], bin, args[1]);
	if (ft_strcmp(args[0], "pwd"))
		bin->exit_code = exec_pwd(inout[1]);
	if (bin->cmd_line->simple_commands[0]->is_builtin == ENV)
		bin->exit_code = exec_env(fdout, bin->env, args);
	if (bin->cmd_line->simple_commands[0]->is_builtin == EXIT)
	{
		bin->exit_code = exec_exit(bin->exit_code, args,
				(bin->cmd_line->pipe_count > 0));
	}
	return (0);
}
