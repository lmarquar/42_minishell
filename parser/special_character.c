/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepical_character.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:44 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/02 15:53:45 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_ctrlchr(char c)
{
	if (c == '|' || c == '&' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_metachr(char c)
{
	if (is_space(c))
		return (1);
	if (is_ctrlchr(c))
		return (1);
	return (0);
}