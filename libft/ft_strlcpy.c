/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:16:46 by chelmerd          #+#    #+#             */
/*   Updated: 2021/11/26 13:04:15 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);

/*
* Description
*	Copy strings with the same input parameters and output result as snprintf(3).
*	Designed to be safer, more consistent, and less error prone replacements for
*	the easily misused function strncpy(3).
*	Take the full size of the destination buffer and guarantee NUL-termination
*	if there is room. Note that room for the NULL should be included in dstsize.
*	Appends string src to the end of dst.
*	Copies up to dstsize - 1 characters from the string src to dst,
*	NUL-terminating the result if dstsize is not 0.
*	If the src and dst strings overlap, the behavior is undefined.

* Return Values
*	The total length of the string tried to create.
*	-> length of src
*	If the return value is >= dstsize, the output string has been truncated.
*	It is the caller's responsibility to handle this.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize < 1)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
