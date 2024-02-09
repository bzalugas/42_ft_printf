/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:58:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 19:28:30 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_buffer	*buff_new(t_type type, size_t len, void *content)
{
	t_buffer	*new;

	new = (t_buffer *)malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->type = type;
	new->len = len;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	buff_add_back(t_buffer **buff, t_buffer *new)
{
	t_buffer	*tmp;

	if (!*buff)
		*buff = new;
	else
	{
		tmp = *buff;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	buff_update_len(new->len);
}

void	*buff_clear(t_buffer **buff)
{
	t_buffer	*tmp;

	while (*buff)
	{
		tmp = (*buff)->next;
		free((*buff)->content);
		free(*buff);
		*buff = tmp;
	}
	return (NULL);
}

size_t	buff_update_len(size_t to_add)
{
	static size_t	total = 0;

	total += to_add;
	return (total);
}
