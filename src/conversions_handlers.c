/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:41:39 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/13 04:40:15 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

bool	handle_char(t_buffer *node, int c)
{
	int		len;
	char	*res;
	bool	minus;
	int		width;

	width = ((t_flags *)node->content)->width;
	minus = ((t_flags *)node->content)->minus;
	len = width + (width < 1);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (false);
	ft_memset(res + minus, ' ', len - 1);
	res[(len - 1 + minus) % len] = (unsigned char)c;
	free(node->content);
	node->content = res;
	node->type = LIT;
	buff_update_len(len);
	node->len = len; // to remove
	return (true);
}
