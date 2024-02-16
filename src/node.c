/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:58:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:48:03 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_node	*node_new(t_type type, int len, void *content)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->len = len;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_node	*node_get_next_conversion(t_node *node)
{
	while (node && (node->type == LIT || node->type == CONVERTED))
		node = node->next;
	return (node);
}
