/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:16:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:38:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static bool	get_adds(char **sp, char **zer, t_flags *f)
{
	if (f->width)
		*sp = (char *)ft_calloc(f->width, sizeof(char));
	if (f->pad)
		*zer = (char *)ft_calloc(f->pad, sizeof(char));
	if (!*sp && f->width && *zer)
	{
		free(*zer);
		return (false);
	}
	if (*sp && !*zer && f->pad)
	{
		free(*sp);
		return (false);
	}
	if (!*sp && !*zer && f->width && f->pad)
		return (false);
	if (*sp && !f->zero)
		ft_memset(*sp, ' ', f->width);
	if (*sp && f->zero)
		ft_memset(*sp, '0', f->width);
	if (*zer)
		ft_memset(*zer, '0', f->pad);
	return (true);
}

static void	modif_adds(char *sp, char *zer, t_flags *f, bool neg)
{
	if (f->pad && neg)
		zer[0] = '-';
	else if (f->pad && f->plus)
		zer[0] = '+';
	else if (f->zero && neg)
		sp[0] = '-';
	else if (f->zero && f->plus)
		sp[0] = '+';
	else if (f->pad && f->space)
		zer[0] = ' ';
}

static bool	int_put_add(t_buffer *buf, t_node *node, bool neg)
{
	char	*sp;
	char	*zer;
	t_flags	*f;

	sp = NULL;
	zer = NULL;
	f = (t_flags *)node->content;
	if (!get_adds(&sp, &zer, f))
		return (false);
	modif_adds(sp, zer, f, neg);
	if (f->minus && !buff_add_after(buf, node, node_new(LIT, f->width, sp)))
		return (false);
	if (!f->minus && f->width && !buff_add_before(buf, node,
									node_new(LIT, f->width, sp)))
		return (false);
	if (f->pad && !buff_add_before(buf, node, node_new(LIT, f->pad, zer)))
		return (false);
	return (true);
}

static bool	handle_flags_int(t_buffer *buf, t_node *node, char *n)
{
	int		len_n;
	t_flags	*f;

	f = (t_flags *)node->content;
	len_n = ft_strlen(n);
	f->zero &= !f->dot && f->width > len_n;
	f->dot &= f->pad > (len_n - n[0] == '-');
	f->minus &= f->width > len_n;
	f->space &= n[0] != '-';
	f->plus &= n[0] != '-';
	f->pad = f->pad - len_n + (n[0] == '-' || f->plus || f->space);
	f->pad = (f->pad > 0) * f->pad;
	f->width = (f->width - len_n - f->pad);
	f->width = (f->width > 0) * f->width;
	return (int_put_add(buf, node, n[0] == '-'));
}

bool	handle_int(t_buffer *buf, t_node *node, int arg)
{
	char	*n;
	t_flags	*f;

	f = (t_flags *)node->content;
	n = ft_itoa_printf(arg, f);
	if (!n)
		return (false);
	if (!handle_flags_int(buf, node, n))
		return (false);
	if ((arg < 0 || f->plus || f->space) && (f->pad || f->zero))
		n[0] = '0';
	free(node->content);
	node->content = n;
	node->len = ft_strlen(n);
	buf->tot_len += node->len;
	return (true);
}

/* bool	handle_uint(t_buffer **buf, t_buffer *node, unsigned int arg) */
/* { */
/* 	char	*n; */


/* } */
