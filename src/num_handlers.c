/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:16:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 13:48:56 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static bool	check_allocs(bool def1, char *s1, bool def2, char *s2)
{
	if (!s1 && def1 && s2)
	{
		free(s2);
		return (false);
	}
	if (s1 && !s2 && def2)
	{
		free(s1);
		return (false);
	}
	if (!s1 && !s2 && def1 && def2)
		return (false);
	return (true);
}

static bool	int_put_add(t_buffer **buf, t_buffer *node)
{
	char	*sp;
	char	*zer;
	t_flags	*f;

	sp = NULL;
	zer = NULL;
	f = (t_flags *)node->content;
	if (f->width)
		sp = (char *)ft_calloc(f->width, sizeof(char));
	if (f->pad)
		zer = (char *)ft_calloc(f->pad, sizeof(char));
	if (!check_allocs(f->width, sp, f->pad, zer))
		return (false);
	if (sp)
		ft_memset(sp, ' ', f->width);
	if (zer)
		ft_memset(zer, '0', f->pad);
	if (f->minus && !buff_add_after(node, buff_new(LIT, f->width, sp)))
		return (false);
	if (!f->minus && f->width && !buff_add_before(buf, node,
						buff_new(LIT, f->width, sp)))
		return (false);
	if (f->pad && !buff_add_before(buf, node, buff_new(LIT, f->pad, zer)))
		return (false);
	return (true);
}

static bool	handle_flags_int(t_buffer **buf, t_buffer *node, char *n)
{
	int		len_n;
	t_flags	*f;

	f = (t_flags *)node->content;
	len_n = ft_strlen(n);
	f->zero &= !f->dot && f->pad > len_n;
	f->dot &= f->pad > len_n;
	f->minus &= f->width > len_n;
	f->pad = (f->pad > 0) * (f->pad - len_n);
	f->width = (f->width > 0) * (f->width - len_n - f->pad);
	return (int_put_add(buf, node));
}

bool	handle_int(t_buffer **buf, t_buffer *node, int arg)
{
	char	*n;
/* /!\ TO HANDLE NEG NUMBERS IN FLAGS /!\ */
	n = ft_itoa(arg);
	if (!n)
		return (false);
	if (!handle_flags_int(buf, node, n))
		return (false);
	free(node->content);
	node->content = n;
	node->len = ft_strlen(n);
	buff_update_len(node->len);
	return (true);
}

/* bool	handle_uint(t_buffer **buf, t_buffer *node, unsigned int arg) */
/* { */
/* 	char	*n; */


/* } */
