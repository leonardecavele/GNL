/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:20:23 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/02 23:57:18 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static short	fetch_size(t_buffer	*buffer, int fd)
{
	size_t	rest_len;

	buffer->readc = read(fd, buffer->buf, BUFFER_SIZE);
	if (buffer->readc == -1)
		buffer->readc = 0;
	buffer->size = buffer->readc;
	rest_len = 0;
	if (*(buffer->rest))
	{
		rest_len = ft_strlen(buffer->rest);
		buffer->size += rest_len;
	}
	if (buffer->size < 1)
		return (0);
	buffer->line = malloc(buffer->size + 1);
	if (!buffer->line)
		return (0);
	buffer->line[0] = 0;
	if (rest_len > 0)
	{
		ft_strlcat(buffer->line, buffer->rest, buffer->size + 1);
		ft_memset(buffer->rest, 0, rest_len);
	}
	return (1);
}

static short	more_size(t_buffer *buffer)
{
	char	*ptr;

	if (buffer->readc < 1)
		return (1);
	buffer->size += buffer->readc;
	ptr = malloc(buffer->size + 1);
	if (!ptr)
	{
		free(buffer->line);
		return (0);
	}
	ft_memcpy(ptr, buffer->line, buffer->size - buffer->readc + 1);
	free(buffer->line);
	ptr[buffer->size] = 0;
	buffer->line = ptr;
	return (1);
}

static void	handle_nl(t_buffer	*buffer, ssize_t nl_i)
{
	size_t	to_del;

	to_del = ft_strlen(buffer->line) - (nl_i + 1);
	ft_memcpy(buffer->rest, &buffer->line[nl_i + 1], to_del);
	buffer->rest[to_del] = 0;
	ft_memset(&buffer->line[nl_i + 1], 0, to_del);
}

char	*get_next_line(int fd)
{
	t_buffer		buffer;
	ssize_t			nl_i;
	static char		rest[BUFFER_SIZE + 1];

	buffer.rest = rest;
	if (BUFFER_SIZE < 1 || fd < 0 || !fetch_size(&buffer, fd))
		return (0);
	nl_i = has_nl(buffer.line);
	while (nl_i < 0 && buffer.readc > 0)
	{
		buffer.buf[buffer.readc] = 0;
		ft_strlcat(buffer.line, buffer.buf, buffer.size + 1);
		nl_i = has_nl(buffer.line);
		if (nl_i > -1)
			break ;
		buffer.readc = read(fd, buffer.buf, BUFFER_SIZE);
		if (!more_size(&buffer))
			return (0);
	}
	if (nl_i > -1)
		handle_nl(&buffer, nl_i);
	return (buffer.line);
}
