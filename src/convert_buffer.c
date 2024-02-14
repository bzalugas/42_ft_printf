/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:43:21 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/14 07:16:47 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	convert_node(t_buffer **buf, t_buffer *node, va_list args)
{
	if (((t_flags *)node->content)->n_star)
		//to implement
	if (node->type == CHAR)
		handle_char(node, va_arg(args, int));
	if (node->type == STR)
		handle_str(buf, node, va_arg(args, char *));
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
