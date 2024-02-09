/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 08:00:35 by bazaluga         ###   ########.fr       */
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
	if (c == 'u' || c == 'x' || c == 'X')
		return (UINT);
	return (PERCENT);
}

static t_buffer	*tokenize(char *str, va_list args)
{
	t_buffer	*buf;
	size_t		i;
	t_flags		*flags;

	buf = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			str[i] = '\0';
			buff_add_back(&buf, buff_new((char *)str, i++, LIT));
			flags = flags_init();
			get_flags(&flags, str, &i, args);
			if (!ft_strchr(SPECIFIERS, str[i]))
				return (buff_clear(&buf));
			buff_add_back(&buf, buff_new(flags, 0, get_type(str[i])));
			str += i + 1;
			i = (size_t) - 1;
		}
		i++;
	}
	if (i > 0)
		buff_add_back(&buf, buff_new((char *)str, i, LIT));
	return (buf);
}
#include <stdio.h>
void	print_buff(t_buffer *buf)
{
	while (buf)
	{
		if (buf->type == LIT)
			write(1, buf->content, buf->len);
		else
		{
			printf("<%d %d %d %d %d %d %d %d>", ((t_flags*)buf->content)->minus,
				((t_flags*)buf->content)->zero, ((t_flags*)buf->content)->dot,
				((t_flags*)buf->content)->sharp, ((t_flags*)buf->content)->space,
				((t_flags*)buf->content)->plus, ((t_flags*)buf->content)->width,
				((t_flags*)buf->content)->pad);
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

	str = ft_strdup(format);
	va_start(args, format);
	buf = tokenize(str, args);
	print_buff(buf);
	free(str);
	/* buff_clear(&buf); */
	va_end(args);
	return (0);
}
