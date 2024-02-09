/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:58:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 03:59:48 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_buffer	*buff_new(void *content, size_t len, t_type type)
{
	t_buffer	*new;

	new = (t_buffer *)malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->content = content;
	new->len = len;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	buff_add_back(t_buffer **buff, t_buffer *new)
{
	t_buffer	*tmp;

	if (!*buff)
		*buff = new;
	tmp = *buff;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
