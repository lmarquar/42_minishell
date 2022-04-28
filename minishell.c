/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:39:02 by chelmerd          #+#    #+#             */
/*   Updated: 2022/04/28 13:00:28 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *arg)
{
	int		fd[2];
	char	*cmd;
	int		pid;
	char	*args[3];
	int		exit_code;

	args[0] = "echo";
	args[1] = arg;
	args[2] = 0;
	cmd = "/bin/echo";
	if (pipe(fd) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
		execve(cmd, args, NULL);
	waitpid(pid, &exit_code, 0);
	if (exit_code != 0 && exit_code != 256)
		perror("program failed");
	return (0);
}

void	handle_signals(int signo)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	if (signo != 2)
		exit(0);
}

int	main(void)
{
	char	*input;

	// init env
	signal(SIGINT, &handle_signals);
	while (1)
	{
		input = readline(SHELL_PROMT);
		if (!input)
		{
			// printf("exit");
			rl_replace_line("minishell>exit", 0);
			rl_redisplay();
			break ;
		}
		add_history(input);
		// check syntax
		// parse / analyse
		// execute
		execute(input);
		free(input);
	}

	return (0);
}
