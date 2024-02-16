/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:58:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 10:40:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_buffer	*buff_new(t_type type, int len, void *content)
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

bool	buff_add_back(t_buffer **buff, t_buffer *new)
{
	t_buffer	*tmp;

	if (!new || !buff)
		return (false);
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
	return (true);
}

bool	buff_add_after(t_buffer *node, t_buffer *new)
{
	if (!node || !new)
		return (false);
	new->next = node->next;
	node->next = new;
	buff_update_len(new->len);
	return (true);
}

bool	buff_add_before(t_buffer **buff, t_buffer *node, t_buffer *new)
{
	t_buffer	*tmp;

	if (!buff || !node || !new)
		return (false);
	new->next = node;
	if (*buff == node)
		*buff = new;
	else
	{
		tmp = *buff;
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		if (!tmp)
			return (false);
		tmp->next = new;
	}
	buff_update_len(new->len);
	return (true);
}

void	buff_reset_node(t_buffer *node)
{
	node->type = 0;
	node->len = 0;
	if (node->content)
		free(node->content);
	node->content = NULL;
	node->next = NULL;
}
