/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:16:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/15 20:19:07 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static bool	flags_put_add(t_buffer **buf, t_buffer *node, int len_a, int len_n)
{
	char	*add;
	t_flags	*f;
	bool	r;

	r = true;
	f = (t_flags *)node->content;
	add = (char *)ft_calloc(len_a + 2, sizeof(char));
	if (!add)
		return (false);
	if (f->dot && f->minus)
	{
		ft_memset(add, '0', f->pad - len_n);
		ft_memset(add + (f->pad - len_n) + 1, ' ', f->width - (f->pad - len_n));
	}
	else if (f->dot)
		ft_memset(add, '0', len_a);
	else if (f->width > 0)
		ft_memset(add, ' ', len_a);
	if (f->dot || (f->width > 0 && !f->minus))
		r = buff_add_before(buf, node, buff_new(LIT, ft_strlen(add), add));
	if (f->width > 0 && f->minus)
		r &= buff_add_after(node, buff_new(LIT,
					ft_strlen(add + (f->pad - len_n) + 1),
					add + (f->pad - len_n) + 1));
	return (r);
}

static bool	handle_flags_int(t_buffer **buf, t_buffer *node, char *n)
{
	int		len_n;
	int		len_add;
	t_flags	*f;
	char	*add;

	f = (t_flags *)node->content;
	len_n = ft_strlen(n);
	len_add = 0;
	f->zero &= !f->dot;
	if (f->dot && f->pad <= len_n)
		f->dot = 0;
	if (f->dot)
		len_add = f->pad - len_n;
	if (f->width > len_n + len_add)
		len_add += f->width - (len_n + len_add);
	else
	{
		f->minus = 0;
		f->width = 0;
	}
	return (flags_put_add(buf, node, len_add, len_n));
}

bool	handle_int(t_buffer **buf, t_buffer *node, int arg)
{

}
