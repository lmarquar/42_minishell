/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_character.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:44 by chelmerd          #+#    #+#             */
/*   Updated: 2022/05/13 12:36:20 by chelmerd         ###   ########.fr       */
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

/*
* 0 = not a quote char
* 1 = single quote
* 2 = double quote
*/
int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
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

int	is_dollarchr(char c)
{
	if (c == '$')
		return (1);
	return (0);
}
