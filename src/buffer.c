/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzalugas <bzalugas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:49:40 by bzalugas          #+#    #+#             */
/*   Updated: 2022/02/05 10:25:17 by bzalugas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buffer	*buffer_new(void)
{
	t_buffer		*new_buf;

	new_buf = malloc(sizeof(t_buffer));
	if (!new_buf)
		return (NULL);
	new_buf->first = NULL;
	return (new_buf);
}

int	buffer_size(t_buffer *buf)
{
	if (buf && buf->first)
		return (buffer_char_size(buf->first));
	else if (buf)
		return (0);
	return (-1);
}

size_t	buffer_print_fd(t_buffer *buf, int fd)
{
	char			*str;
	int				i;
	t_buffer_char	*next_char;

	if (!buf)
		return (0);
	str = malloc(sizeof(char) * buffer_size(buf) + 1);
	if (!str)
		return (0);
	next_char = buf->first;
	i = 0;
	while (next_char && i < buffer_size(buf))
	{
		str[i++] = next_char->c;
		next_char = next_char->next;
	}
	str[i] = '\0';
	write(fd, str, buffer_size(buf));
	free(str);
	return (buffer_size(buf));
}

void	buffer_close(t_buffer **buf)
{
	buffer_char_clear(&(*buf)->first);
	free(*buf);
	*buf = NULL;
}
