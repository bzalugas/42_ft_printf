/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/13 17:09:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_type	get_type(char c) // in utils ?
{
	if (c == 'c')
		return (CHAR);
	if (c == 's')
		return (STR);
	if (c == 'p')
		return (PTR);
	if (c == 'd' || c == 'i')
		return (INT);
	if (c == 'u')
		return (UINT);
	if (c == 'x')
		return (LHEX);
	if (c == 'X')
		return (UHEX);
	if (c == '%')
		return (PERCENT);
	return (ERR);
}

static bool	parse(t_buffer **buf, char *str, int *i, va_list args)
{
	t_flags	*flags;
	t_type	type;

	if (*i > 0)
	{
		str[*i] = '\0';
		if (!buff_add_back(buf, buff_new(LIT, (*i)++, str)))
			return (false);
	}
	else
		++(*i);
	if (!flags_get(&flags, str, i, args))
		return (false);
	type = get_type(str[*i]);
	if (type == ERR || !buff_add_back(buf, buff_new(type, 0, flags)))
	{
		free(flags);
		return (false);
	}
	return (true);
}

static int	tokenize(t_buffer **buf, char *str, va_list args)
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
		return (buff_add_back(buf, buff_new(LIT, i, str)) - 1);
	return (0);
}
#include <stdio.h>
void	print_buff(t_buffer *buf)
{
	printf("total len = %d\n", buff_update_len(0));
	while (buf)
	{
		if (buf->type == LIT)
			write(1, buf->content, buf->len);
		else
		{
			printf("<-:%d 0:%d .:%d #:%d s:%d +:%d w:%d p:%d type:%d>",
				((t_flags*)buf->content)->minus,
				((t_flags*)buf->content)->zero, ((t_flags*)buf->content)->dot,
				((t_flags*)buf->content)->sharp, ((t_flags*)buf->content)->space,
				((t_flags*)buf->content)->plus, ((t_flags*)buf->content)->width,
				((t_flags*)buf->content)->pad, buf->type);
			fflush(stdout);
		}

		buf = buf->next;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_buffer	*buf;
	char		*str;
	int			count;

	buf = NULL;
	if (!format)
		return (-1);
	str = ft_strdup(format);
	va_start(args, format);
	count = tokenize(&buf, str, args);
	if (!buf)
		return (-1);
	convert_buffer(&buf, args);
	print_buff(buf);
	if (!count)
		count = buff_update_len(0);
	free(str);
	buff_clear(&buf);
	va_end(args);
	return (count);
}
