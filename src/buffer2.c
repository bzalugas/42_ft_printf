/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:29:26 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/20 12:21:18 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	*buff_clear(t_buffer **buf)
{
	t_node	*tmp;
	t_node	*tmp2;

	if (!buf || !*buf)
		return (NULL);
	tmp = (*buf)->first;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->type != LIT)
			free(tmp->content);
		free(tmp);
		tmp = tmp2;
	}
	free(*buf);
	return (NULL);
}

static size_t	buffcpy(char *dst, t_buffer *buf)
{
	int		tot;
	t_node	*node;

	tot = 0;
	node = buf->first;
	while (node)
	{
		if (node->len > 0)
		{
			if (!ft_memcpy(dst + tot, node->content, node->len))
				return (tot);
			tot += node->len;
		}
		node = node->next;
	}
	return (tot);
}

size_t	buff_print(t_buffer *buf)
{
	char	*str;
	ssize_t	ret;

	if (!buf)
		return (0);
	str = (char *)ft_calloc(buf->tot_len + 1L, sizeof(char));
	if (!str)
		return (0);
	if (buffcpy(str, buf) != buf->tot_len)
	{
		free(str);
		return (0);
	}
	ret = write(1, str, buf->tot_len);
	while (ret != (ssize_t)buf->tot_len)
	{
		if (ret == -1)
		{
			free(str);
			return (0);
		}
		ret += write(1, str, buf->tot_len - ret);
	}
	free(str);
	return ((int)ret);
}
