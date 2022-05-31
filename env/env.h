/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:27:14 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/28 14:50:26 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_env_var
{
	char				*key;
	char				*val;
	struct s_env_var	*next;
}	t_env_var;

// single

t_env_var	*new_env_var(char *key, char *value);
void		clear_env_var(t_env_var *env);
char		*stringify(t_env_var *env, int wrap_in_quotes);
t_env_var	*get_env_from_str(char *env_str);

// list

size_t		env_var_len(t_env_var *env);
t_env_var	*add_env_var(t_env_var **lst, t_env_var *var);
t_env_var	*remove_env_var(t_env_var *env, const char *key);
void		clear_env_vars(t_env_var *lst);
char		*find_in_env(char *key, size_t key_len, t_env_var *env_vars);

#endif
