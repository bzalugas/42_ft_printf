/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:43:21 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/17 02:11:25 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static bool	convert_node(t_buffer *buf, t_node *node, va_list args)
{
	bool	check;

	if (((t_flags *)node->content)->n_star)
		va_arg(args, int);
	if (node->type == CHAR)
		check = handle_char(buf, node, va_arg(args, int));
	if (node->type == STR)
		check = handle_str(buf, node, va_arg(args, const char *));
	if (node->type == INT)
		check = handle_int(buf, node, va_arg(args, int));
	if (node->type == UINT)
		check = handle_uint(buf, node, va_arg(args, unsigned int));
	if (node->type == LHEX || node->type == UHEX)
		check = handle_hex(buf, node, va_arg(args, unsigned int));
	if (node->type == PTR)
		check = handle_ptr(buf, node, va_arg(args, void *));
	if (node->type == PERCENT)
		check = handle_percent(buf, node);
	node->type = CONV;
	return (check);
}

bool	convert_buffer(t_buffer *buf, va_list args)
{
	t_node	*node;

	node = node_get_next_conversion(buf->first);
	while (node)
	{
		if (!convert_node(buf, node, args))
			return (false);
		node = node_get_next_conversion(node);
	}
	return (true);
}
