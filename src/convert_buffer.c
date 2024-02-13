/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:43:21 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/13 04:16:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	convert_node(t_buffer **buf, t_buffer *node, va_list args)
{
	if (node->type == CHAR)
		handle_char(node, va_arg(args, int));
	(void)buf;

}

bool	convert_buffer(t_buffer **buf, va_list args)
{
	t_buffer	*node;

	node = buff_get_next_conversion(*buf);
	while (node)
	{
		convert_node(buf, node, args);
		node = buff_get_next_conversion(node);
	}
	return (true);
}
