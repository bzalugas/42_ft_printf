/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:29:26 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:47:26 by bazaluga         ###   ########.fr       */
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

/* int	buff_update_len(size_t to_add) */
/* { */
/* 	static int	total = 0; */

/* 	total += to_add; */
/* 	return (total); */
/* } */
