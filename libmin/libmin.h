/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:56:50 by lmarquar          #+#    #+#             */
/*   Updated: 2022/06/07 14:58:04 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_H
# define LIBMIN_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_ci(const char *s1, const char *s2);
int		ft_strccmp(const char *s1, const char *s2, char c);
int		my_rl_go_on_nl(void);
int		custom_error(int error_code, char *builtin_name, char *msg);

#endif
