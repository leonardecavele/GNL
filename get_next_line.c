/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:23 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/08 22:47:29 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static short	allocl(t_reader *b)
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
		ft_nllstrcpy(tmp, b->line, b->bf_i + 1);
		free(b->line);
	}
	tmp[b->bf_i] = 0;
	b->line = tmp;
	return (1);
}

static short	handle_r(t_reader *b)
{
	static char	r[BUFFER_SIZE + 1];

	b->r = r;
	if (!*r)
		return (1);
	b->nread = 0;
	while (b->r[b->nread])
		b->nread++;
	if (!allocl(b))
		return (0);
	ft_nllstrcpy(b->line, b->r, b->nread);
	b->bf_i = b->nread;
	ft_memset(b->r, 0, b->nread);
	b->nl_i = has_nl(b->line, b->nread);
	return (1);
}

static short	init_b(t_reader *b)
{
	b->bf_i = 0;
	b->nl_i = -1;
	b->line = 0;
	b->b = malloc(BUFFER_SIZE);
	if (!b->b)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	t_reader		b;
	size_t			ndel;

	if (BUFFER_SIZE < 1 || fd < 0 || !init_b(&b) || !handle_r(&b))
		return (0);
	while (b.nl_i < 0)
	{
		b.nread = read(fd, b.b, BUFFER_SIZE);
		if (b.nread < 1)
			break ;
		if (!allocl(&b))
			return (0);
		ft_nllstrcpy(&b.line[b.bf_i], b.b, b.nread);
		b.bf_i += b.nread;
		b.nl_i = has_nl(b.b, b.nread);
	}
	if (b.nl_i > -1)
	{
		ndel = b.bf_i - (b.bf_i - b.nread + b.nl_i + 1);
		ft_nllstrcpy(b.r, &b.line[b.bf_i - b.nread + b.nl_i + 1], ndel);
		ft_memset(&b.line[b.bf_i - b.nread + b.nl_i + 1], 0, ndel);
	}
	free(b.b);
	return (b.line);
}
