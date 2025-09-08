/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:23 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/08 17:25:00 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static short	allocb(t_buffer *buffer)
{
	char	*temp;

	temp = malloc(buffer->len + buffer->readc + 1);
	if (!temp)
	{
		free(buffer->buf);
		if (buffer->line)
			free(buffer->line);
		return (0);
	}
	if (buffer->line)
	{
		ft_memcpy(temp, buffer->line, buffer->len + 1);
		free(buffer->line);
	}
	temp[buffer->len] = 0;
	buffer->line = temp;
	return (1);
}

static void	handle_nl(t_buffer	*buffer, ssize_t lnl_i)
{
	size_t	to_del;

	to_del = buffer->len - (lnl_i + 1);
	ft_memcpy(buffer->rest, &buffer->line[lnl_i + 1], to_del);
	buffer->rest[to_del] = 0;
	ft_memset(&buffer->line[lnl_i + 1], 0, to_del);
}

static short	init(t_buffer *buffer)
{
	static char	rest[BUFFER_SIZE + 1] = "";

	buffer->line = 0;
	buffer->len = 0;
	buffer->rest = rest;
	buffer->bnl_i = -1;
	buffer->buf = malloc(BUFFER_SIZE);
	if (!buffer->buf)
		return (0);
	if (!*rest)
		return (1);
	buffer->readc = ft_strlen(buffer->rest);
	if (!allocb(buffer))
		return (0);
	ft_memcpy(buffer->line, buffer->rest, buffer->readc);
	buffer->line[buffer->readc] = 0;
	buffer->len = buffer->readc;
	ft_memset(buffer->rest, 0, buffer->readc);
	buffer->bnl_i = has_nl(buffer->line, buffer->readc);
	return (1);
}

char	*get_next_line(int fd)
{
	t_buffer		buffer;

	if (BUFFER_SIZE < 1 || fd < 0 || !init(&buffer))
		return (0);
	while (buffer.bnl_i < 0)
	{
		buffer.readc = read(fd, buffer.buf, BUFFER_SIZE);
		if (buffer.readc < 1)
			break ;
		if (!allocb(&buffer))
			return (0);
		ft_memcpy(&buffer.line[buffer.len], buffer.buf, buffer.readc);
		buffer.len += buffer.readc;
		buffer.line[buffer.len] = 0;
		buffer.bnl_i = has_nl(buffer.buf, buffer.readc);
	}
	if (buffer.bnl_i > -1)
		handle_nl(&buffer, buffer.len - buffer.readc + buffer.bnl_i);
	free(buffer.buf);
	return (buffer.line);
}
