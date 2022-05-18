/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:39:02 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/18 09:50:34 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
	}
	rl_redisplay();
}

int	init_env(char *envp[], t_env_var **e_v)
{
	t_env_var	*var;
	t_env_var	*last;
	size_t		i;

	i = 0;
	while (envp[i])
	{
		var = get_env_from_str(envp[i]);
		if (i > 0)
			last->next = var;
		if (!*e_v)
			*e_v = var;
		last = var;
		i++;
	}
	return (0);
}

int	init_bin(t_bin **bin, t_env_var *env_vars)
{
	*bin = ft_calloc(1, sizeof(t_bin));
	(*bin)->env = env_vars;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_var	*env_vars;
	t_bin		*bin;
	t_cmd_line	cmd_line;

	(void) argc;
	(void) argv;
	init_env(envp, &env_vars);
	init_bin(&bin, env_vars);
	while (1)
	{
		signal(SIGINT, &handle_signals);
		signal(SIGQUIT, SIG_IGN);
		bin->in = readline(SHELL_PROMT);
		if (!bin->in)
			bin->in = ft_strdup("exit");
		add_history(bin->in);
		if (parse(bin->in, &cmd_line, env_vars, bin) == 0)
		{
			execute(bin);
		}
		clear_cmd_line(&cmd_line);
		free(bin->in);
	}
	// clear list of env_vars

	return (0);
}
