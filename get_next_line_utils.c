/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:21:14 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/08 16:46:30 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	while (dst_len < size && dst[dst_len])
		dst_len++;
	src_len = ft_strlen(src);
	if (dst_len == size)
		return (dst_len + src_len);
	i = -1;
	while (src[++i] && dst_len + i + 1 < size)
		dst[dst_len + i] = src[i];
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	while (n--)
		((t_u8p)dst)[n] = ((t_u8p)src)[n];
	return (dst);
}

ssize_t	has_nl(char *s, ssize_t n)
{
	ssize_t	i;

	i = -1;
	while (++i < n && s[i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((t_u8p)s)[n] = (t_u8)c;
	return (s);
}
