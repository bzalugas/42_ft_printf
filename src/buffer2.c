/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:29:26 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/13 02:29:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	*buff_clear(t_buffer **buff)
{
	t_buffer	*tmp;

	while (*buff)
	{
		tmp = (*buff)->next;
		if ((*buff)->type != LIT)
			free((*buff)->content);
		free(*buff);
		*buff = tmp;
	}
	return (NULL);
}

int	buff_update_len(size_t to_add)
{
	static int	total = 0;

	total += to_add;
	return (total);
}
