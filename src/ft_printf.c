/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 18:48:57 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_type	get_type(char c) // in utils ?
{
	if (c == 'c')
		return (CHAR);
	if (c == 's')
		return (STR);
	if (c == 'd' || c == 'i')
		return (INT);
	if (c == 'u')
		return (UINT);
	if (c == 'x')
		return (LHEX);
	if (c == 'X')
		return (UHEX);
	if (c == 'p')
		return (PTR);
	if (c == '%')
		return (PERCENT);
	return (ERR);
}

static bool	parse(t_buffer *buf, char *str, int *i, va_list args)
{
	t_flags	*flags;
	t_type	type;

	if (*i > 0)
	{
		str[*i] = '\0';
		if (!buff_add_back(buf, node_new(LIT, (*i)++, str)))
			return (false);
	}
	else
		++(*i);
	if (!flags_get(&flags, str, i, args))
		return (false);
	type = get_type(str[*i]);
	if (type == ERR || !buff_add_back(buf, node_new(type, 0, flags)))
	{
		free(flags);
		return (false);
	}
	return (true);
}

static int	tokenize(t_buffer *buf, char *str, va_list args)
{
	int		i;

	bool	check;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			check = parse(buf, str, &i, args);
			if (!check)
				return (-1);
			str += i + 1;
			i = -1;
		}
		i++;
	}
	if (i > 0)
		return (buff_add_back(buf, node_new(LIT, i, str)) - 1);
	return (0);
}
#include <stdio.h>
void	print_buff(t_buffer *buf)
{
	t_node	*node;

	printf("total len = %d\n", buf->tot_len);
	node = buf->first;
	while (node)
	{
		if (node->type == LIT || node->type == CONVERTED)
			write(1, node->content, node->len);
		else
		{
			printf("<-:%d 0:%d .:%d #:%d s:%d +:%d w:%d p:%d type:%d>",
				((t_flags*)node->content)->minus,
				((t_flags*)node->content)->zero, ((t_flags*)node->content)->dot,
				((t_flags*)node->content)->sharp, ((t_flags*)node->content)->space,
				((t_flags*)node->content)->plus, ((t_flags*)node->content)->width,
				((t_flags*)node->content)->pad, node->type);
			fflush(stdout);
		}

		node = node->next;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_buffer	*buf;
	char		*str;
	int			count;

	if (!format)
		return (-1);
	buf = buff_init();
	if (!buf)
		return (-1);
	str = ft_strdup(format);
	va_start(args, format);
	count = tokenize(buf, str, args);
	if (!buf)
		return (-1);
	convert_buffer(buf, args);
	print_buff(buf);
	if (!count)
		count = buf->tot_len;
	free(str);
	buff_clear(&buf);
	va_end(args);
	return (count);
}
