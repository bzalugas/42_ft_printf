/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_str_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:41:39 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:35:58 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

bool	handle_char(t_buffer *buf, t_node *node, int c)
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
	buf->tot_len += len;
	node->len = len;
	return (true);
}

static bool	handle_flags_str(t_buffer *buf, t_node *node, const char *str)
{
	int			len_add;
	int			len_str;
	t_flags		*f;
	char		*add;

	len_add = 0;
	f = (t_flags *)node->content;
	len_str = ft_strlen(str);
	if (f->dot && f->pad > len_str)
		f->dot = 0;
	if (f->dot && f->width > len_str - (len_str - f->pad))
		len_add = f->width - (len_str - (len_str - f->pad));
	else if(!f->dot)
		len_add = f->width - len_str;
	if (len_add < 1)
		return (true);
	add = (char *)ft_calloc(len_add + 1, sizeof(char));
	if (!add)
		return (false);
	ft_memset(add, ' ', len_add);
	if (f->minus && f->width)
		return (buff_add_after(buf, node, node_new(LIT, len_add, add)));
	return (buff_add_before(buf, node, node_new(LIT, len_add, add)));
}

bool	handle_str(t_buffer *buf, t_node *node, const char *str)
{
	t_flags	*f;

	if (!handle_flags_str(buf, node, str))
		return (false);
	f = (t_flags *)node->content;
	if (f->dot)
		node->content = ft_strndup(str, f->pad);
	else
		node->content = ft_strdup(str);
	node->type = LIT;
	node->len = ft_strlen((char *)node->content);
	buf->tot_len += node->len;
	free(f);
	return (true);
}
