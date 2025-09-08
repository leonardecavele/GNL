/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:21:14 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/08 19:10:10 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_nllstrcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	if (n)
		((t_u8p)dst)[n] = 0;
	while (n--)
		((t_u8p)dst)[n] = ((t_u8p)src)[n];
	return (dst);
}

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((t_u8p)s)[n] = (t_u8)c;
	return (s);
}

ssize_t	has_nl(char *s, ssize_t n)
{
	ssize_t	i;

	i = -1;
	while (++i < n)
		if (s[i] == '\n')
			return (i);
	return (-1);
}
