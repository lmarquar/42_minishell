/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:39:02 by chelmerd          #+#    #+#             */
/*   Updated: 2022/04/28 16:55:11 by leon             ###   ########.fr       */
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

int	init_env(t_env_var **e_v)
{
	(*e_v) = NULL;
	(*e_v) = malloc(sizeof(t_env_var));
	(*e_v)->key = "$";
	(*e_v)->val = "86545";	
	(*e_v)->next = NULL;
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*find_in_env(char *key, t_env_var *env_vars)
{
	while (env_vars && strcmp(env_vars->key, key) != 0)
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

	offset = 0;

	result = malloc(sizeof(char) * (strlen(str) * strlen(val)));
       	
	start = strstr(str, key);
	strncpy(result, str, (start - str));
	offset = start - str;
       	strcpy(result + offset, val);
	offset += strlen(val);
	strcpy(result + offset, start + strlen(key));
	free(str);
	return (result);		
}

int	expand_env_vars(char **input, t_env_var *env_vars)
{
	int	i;
	char	*mark;
	int	k;
	char	*var_key;
	char	*var_val;
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
			strncpy(var_key, mark, k);
			var_key[k] = '\0';
			var_val = find_in_env(var_key, env_vars);
			in = replace_word(in, ft_strjoin("$", var_key), var_val);
			i = i + k;
			free(var_key);
		}
		i++;
	}
	*input = in;
	return(0);
}

int	main(void)
{
	char	*input;
	t_env_var	*env_vars; 

	// init env
	init_env(&env_vars);
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
		// transform env_vars
		expand_env_vars(&input, env_vars);
		// check syntax
		// parse / analyse
		// execute
		execute(input);
		free(input);
	}

	return (0);
}
