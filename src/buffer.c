/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:58:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/08 18:10:29 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_buffer	*buff_new(char	*str, size_t len)
{
	t_buffer	*new;

	new = (t_buffer *)malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->str = str;
	new->len = len;
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

void	buff_clear(t_buffer **buff)
{
	t_buffer	*tmp;

	if (!*buff)
		return ;
	while (*buff)
	{
		tmp = (*buff)->next;
		free((*buff)->str);
		free(*buff);
		*buff = tmp;
	}
}
