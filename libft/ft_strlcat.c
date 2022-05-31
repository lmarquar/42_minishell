/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:36:22 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:01:23 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);

/*
* Description
*	Copy and concatenate strings with the same input parameters and output result
*	as snprintf(3).
*	Designed to be safer, more consistent, and less error prone replacements for
*	the easily misused function strncat(3).
*	Take the full size of the destination buffer and guarantee NUL-termination
*	if there is room. Note that room for the NULL should be included in dstsize.
*	Appends string src to the end of dst.
*	It will append at most dstsize - strlen(dst) - 1 characters.  It will then
*	NUL-terminate, unless dstsize is 0 or the original dst string was longer than
*	dstsize (in practice this should not happen as it means that either dstsize
*	is incorrect or that dst is not a proper string).
*	If the src and dst strings overlap, the behavior is undefined.

* Return Values
*	The total length of the string tried to create.
*	-> initial length of dst plus the length of src
*	If the return value is >= dstsize, the output string has been truncated.
*	It is the caller's responsibility to handle this.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		dst_len;

	d = dst;
	s = src;
	n = dstsize;
	while (*d && n-- != 0)
		d++;
	dst_len = d - dst;
	n = dstsize - dst_len;
	if (n == 0)
		return (dst_len + ft_strlen(s));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dst_len + (s - src));
}
