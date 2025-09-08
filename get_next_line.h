/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/08 19:10:11 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef unsigned char	*t_u8p;
typedef unsigned char	t_u8;

typedef struct s_reader
{
	char			*line;
	char			*r;
	char			*b;
	ssize_t			nread;
	ssize_t			nl_i;
	size_t			bf_i;
}					t_reader;

char	*get_next_line(int fd);

//utils
void	*ft_nllstrcpy(void *dst, const void *src, size_t n);
ssize_t	has_nl(char *s, ssize_t n);
void	*ft_memset(void *s, int c, size_t n);

#endif
