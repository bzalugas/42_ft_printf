/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 07:50:44 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	handle_flag_nb(char *str, size_t *i, va_list args)
{
	va_list		tmp;
	int			nb;
	int			n_arg;

	n_arg = ft_atoi(str);
	while (str[*i] && ft_isdigit(str[*i]))
		(*i)++;
	if (!str[*i] || str[*i] != '$')
		return (-1);
	va_copy(tmp, args);
	nb = -1;
	if (n_arg == 0 || n_arg == 1)
		nb = va_arg(tmp, int);
	else
		while (--n_arg > 0)
			nb = va_arg(tmp, int);
	va_end(tmp);
	return (nb);
}

static void	get_flags(t_flags **flags, char *str, size_t *i, va_list args)
{
	while (str[*i] && (ft_strchr(FLAGS, str[*i]) || ft_isdigit(str[*i])))
	{
		(*flags)->minus |= str[*i] == '-';
		(*flags)->zero |= str[*i] == '0';
		(*flags)->dot |= str[*i] == '.';
		(*flags)->sharp |= str[*i] == '#';
		(*flags)->space |= str[*i] == ' ';
		(*flags)->plus |= str[*i] == '+';
		if (str[*i] == '*' && (*flags)->dot)
			(*flags)->pad = handle_flag_nb(str, i, args);
		else if (str[*i] == '*')
			(*flags)->width = handle_flag_nb(str, i, args);
		else if (ft_isdigit(str[*i]) && str[*i] != '0')
		{
			if (*i > 0 && str[(*i) - 1] == '.' && (*flags)->zero)
				(*flags)->width = (*flags)->pad;
			if ((*flags)->dot || (*flags)->zero)
				(*flags)->pad = ft_atoi(&str[*i]);
			else
				(*flags)->width = ft_atoi(&str[*i]);
			while (str[*i] && ft_isdigit(str[*i]))
				(*i)++;
		}
		else
			(*i)++;
	}
}

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
