/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:43:21 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:46:48 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	convert_node(t_buffer *buf, t_node *node, va_list args)
{
	if (((t_flags *)node->content)->n_star)//only for *, not for *x$
		va_arg(args, int);
	if (node->type == CHAR)
		handle_char(buf, node, va_arg(args, int));
	if (node->type == STR)
		handle_str(buf, node, va_arg(args, const char *));
	if (node->type == INT)
		handle_int(buf, node, va_arg(args, int));
	node->type = CONVERTED;
}

bool	convert_buffer(t_buffer *buf, va_list args)
{
	t_node	*node;

	node = node_get_next_conversion(buf->first);
	while (node)
	{
		convert_node(buf, node, args);
		node = node_get_next_conversion(node);
	}
	return (true);
}
