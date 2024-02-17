/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:29:26 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/17 02:53:32 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	*buff_clear(t_buffer **buf)
{
	t_node	*tmp;
	t_node	*tmp2;

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
	size_t	ret;
	size_t	tot;
	t_node	*node;

	ret = 0;
	tot = 0;
	node = buf->first;
	while (node)
	{
		if (node->len > 0)
		{
			ret = ft_strlcpy(dst + tot, (const char *)node->content, node->len + 1);
			if (dst[tot] != 0 && ret != (size_t)node->len)
				return (0);
			tot += ret + (dst[tot] == 0);
		}
		node = node->next;
	}
	return (tot);
}

int	buff_print(t_buffer *buf)
{
	char	*str;
	ssize_t	ret;

	if (!buf)
		return (0);
	str = (char *)ft_calloc(buf->tot_len + 1, sizeof(char));
	if (!str)
		return (0);
	if (buffcpy(str, buf) != (size_t)buf->tot_len)
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

/* int	buff_update_len(size_t to_add) */
/* { */
/* 	static int	total = 0; */

/* 	total += to_add; */
/* 	return (total); */
/* } */
