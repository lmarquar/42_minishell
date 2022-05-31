/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:56:50 by lmarquar          #+#    #+#             */
/*   Updated: 2022/05/31 15:07:42 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_H
# define LIBMIN_H

# include "../libft/libft.h"

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_ci(const char *s1, const char *s2);
int		ft_strccmp(const char *s1, const char *s2, char c);

#endif