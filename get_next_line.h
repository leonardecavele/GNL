/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/02 23:54:27 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef unsigned char	*t_u8p;
typedef unsigned char	t_u8;

typedef struct s_buffer
{
	char			*line;
	size_t			size;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			readc;
	char			*rest;
}					t_buffer;

char	*get_next_line(int fd);

//utils
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
ssize_t	has_nl(char *s);
void	*ft_memset(void *s, int c, size_t n);

#endif
