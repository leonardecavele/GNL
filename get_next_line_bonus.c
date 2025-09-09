/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:23 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/09 14:30:43 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdbool.h>

static bool	allocl(t_reader *b)
{
	char	*tmp;

	tmp = malloc(b->bf_i + b->nread + 1);
	if (!tmp)
	{
		free(b->b);
		free(b->line);
		return (0);
	}
	if (b->line)
	{
		nllstrcpy(tmp, b->line, b->bf_i + 1);
		free(b->line);
	}
	tmp[b->bf_i] = 0;
	b->line = tmp;
	return (1);
}

static bool	handle_r(t_reader *b, int fd)
{
	static char	*r[FD_MAX];

	if (!r[fd])
	{
		r[fd] = malloc(BUFFER_SIZE + 1);
		if (!r[fd])
			return (0);
		ft_memset(r[fd], 0, BUFFER_SIZE);
	}
	b->r = &r[fd];
	if (!**b->r)
		return (1);
	b->nread = 0;
	while ((*b->r)[b->nread])
		b->nread++;
	if (!allocl(b))
		return (0);
	nllstrcpy(b->line, *b->r, b->nread);
	b->bf_i = b->nread;
	ft_memset(*b->r, 0, b->nread);
	b->nl_i = get_nl(b->line, b->nread);
	return (1);
}

static bool	init_b(t_reader *b)
{
	b->bf_i = 0;
	b->nl_i = -1;
	b->line = 0;
	b->b = malloc(BUFFER_SIZE);
	if (!b->b)
		return (0);
	return (1);
}

static char	*handle_eof(t_reader *b)
{
	free(*b->r);
	*b->r = 0;
	free(b->b);
	return (b->line);
}

char	*get_next_line(int fd)
{
	size_t		ndel;
	t_reader	b;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > FD_MAX
		|| !init_b(&b) || !handle_r(&b, fd))
		return (NULL);
	while (b.nl_i < 0)
	{
		b.nread = read(fd, b.b, BUFFER_SIZE);
		if (b.nread < 1)
			return (handle_eof(&b));
		if (!allocl(&b))
			return (NULL);
		nllstrcpy(&b.line[b.bf_i], b.b, b.nread);
		b.bf_i += b.nread;
		b.nl_i = get_nl(b.b, b.nread);
	}
	if (b.nl_i > -1)
	{
		ndel = b.bf_i - (b.bf_i - b.nread + b.nl_i + 1);
		nllstrcpy(*b.r, &b.line[b.bf_i - b.nread + b.nl_i + 1], ndel);
		ft_memset(&b.line[b.bf_i - b.nread + b.nl_i + 1], 0, ndel);
	}
	free(b.b);
	return (b.line);
}
