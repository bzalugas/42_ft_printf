/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 06:55:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	handle_flag_nb(char *format, size_t *i, va_list args)
{
	va_list		tmp;
	int			nb;
	int			n_arg;

	n_arg = ft_atoi(format);
	while (format[*i] && ft_isdigit(format[*i]))
		(*i)++;
	if (!format[*i] || format[*i] != '$')
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

static t_flags	*get_flags(char *format, size_t *i, va_list args)
{
	t_flags *flags;

	flags = flags_init();
	while (format[*i] && (ft_strchr(FLAGS, format[*i]) || ft_isdigit(format[*i])))
	{
		flags->minus |= format[*i] == '-';
		flags->zero |= format[*i] == '0';
		flags->dot |= format[*i] == '.';
		flags->sharp |= format[*i] == '#';
		flags->space |= format[*i] == ' ';
		flags->plus |= format[*i] == '+';
		if (format[*i] == '*' && flags->dot)
			flags->pad = handle_flag_nb(format, i, args);
		else if (format[*i] == '*')
			flags->width = handle_flag_nb(format, i, args);
		else if (ft_isdigit(format[*i]) && format[*i] != '0')
		{
			if (flags->dot || flags->zero)
				flags->pad = ft_atoi(&format[*i]);
			else
				flags->width = ft_atoi(&format[*i]);
			while (format[*i] && ft_isdigit(format[*i]))
				(*i)++;
		}
		else
			(*i)++;
	}
	return (flags);
}

static t_type	get_type(char c) // in utils ?
{
	if (c == 'c')
		return CHAR;
	if (c == 's')
		return STR;
	if (c == 'p')
		return PTR;
	if (c == 'd' || c == 'i')
		return INT;
	if (c == 'u' || c == 'x' || c == 'X')
		return UINT;
	return PERCENT;
}

static t_buffer	*tokenize(char *format, va_list args)
{
	t_buffer	*buf;
	size_t		i;
	t_flags		*flags;

	buf = NULL;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			format[i] = '\0';
			buff_add_back(&buf, buff_new((char *)format, i++, LIT));
			flags = get_flags(format, &i, args);
			if (!ft_strchr(SPECIFIERS, format[i]))
				return (buff_clear(&buf));
			buff_add_back(&buf, buff_new(flags, 0, get_type(format[i])));
			format += i + 1;
			i = (size_t)-1;
		}
		i++;
	}
	if (i > 0)
		buff_add_back(&buf, buff_new((char *)format, i, LIT));
	return (buf);
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	t_buffer	*buf;
	char		*str;

	str = ft_strdup(format);
	va_start(args, format);
	buf = tokenize(str, args);
	t_buffer *tmp = buf;
	while (tmp)
	{
		if (tmp->type == LIT)
			write(1, tmp->content, tmp->len);
		else
			write(1, "<CONVERSION>", 12);
		tmp = tmp->next;
	}
	free(str);
	buff_clear(&buf);
	va_end(args);
	return (0);
}
