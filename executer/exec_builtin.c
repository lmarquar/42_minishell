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

int	exec_builtin(t_bin *bin, char **args, int fdout)
{
	if (ft_strcmp(args[0], "echo"))
		bin->exit_code = exec_echo(fdout, args);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == ENV)
		bin->exit_code = exec_env(fdout, bin->env, args);
	else if (ft_strcmp(args[0], "pwd"))
		bin->exit_code = exec_pwd(fdout);
	else if (ft_strcmp(args[0], "export") && !args[1])
	{
		write(1, "execute here\n", 14);
		bin->exit_code = exec_export(fdout, bin, args[1]);
	}
	else if (bin->cmd_line->smp_cmds[1])
		return (0);
	else if (ft_strcmp(args[0], "export"))
		bin->exit_code = exec_export(fdout, bin, args[1]);
	else if (ft_strcmp(args[0], "cd"))
		bin->exit_code = exec_cd(args[1]);
	else if (ft_strcmp(args[0], "unset"))
		bin->exit_code = exec_unset(args[1], bin);
	else if (bin->cmd_line->smp_cmds[0]->is_builtin == EXIT)
	{
		bin->exit_code = exec_exit(bin->exit_code, args,
				(bin->cmd_line->pipe_count > 0));
	}
	return (0);
}
