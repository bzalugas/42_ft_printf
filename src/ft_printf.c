/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 04:12:06 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	handle_flag_nb(const char *format, va_list args)
{
	va_list		tmp;
	size_t		i;
	int			nb;
	int			n_arg;

	n_arg = ft_atoi(format);
	i = 0;
	while (format[i] && ft_isdigit(format[i]))
		i++;
	if (!format[i] || format[i] != '$')
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

t_flags	*get_flags(const char *format, size_t *i, va_list args)
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
			flags->pad = handle_flag_nb(&format[++(*i)], args);
		else if (format[*i] == '*')
			flags->width = handle_flag_nb(&format[++(*i)], args);
		else if (ft_isdigit(format[*i]) && format[*i] != '0')
		{
			if (flags->minus || flags->min_width)
				flags->width = ft_atoi(&format[*i]);
			else if (flags->dot || flags->zero)
				flags->pad = ft_atoi(&format[*i]);
		}
		while (format[*i] && ft_isdigit(format[*i]))
			(*i)++;
	}
	return (flags);
}

/* char		*get_conversion(const char *format, va_list args) */
/* { */
/* 	t_flags	flags; */

/* 	//get flags */

/* 	//convert */
/* 	//process flags */
/* 	//return created str */
/* } */

t_type	get_type(char c) // in utils ?
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

t_buffer	*tokenize(const char *format, va_list args)
{
	t_buffer	*buf;
	size_t		i;
	t_flags		*flags;

	buf = NULL;
	i = 0;
	while (format[i])
	{
		if (ft_strchr(SPECIFIERS, format[i]))
		{
			buff_add_back(&buf, buff_new((char *)format, i, LIT));
			flags = get_flags(format, &i, args);
			if (!ft_strchr(SPECIFIERS, format[i]))
				return (buff_clear(&buf));
			buff_add_back(&buf, buff_new(flags, 0, get_type(format[i])));
		}
		i++;
	}
	return (buf);
}

int		ft_printf(const char *format, ...)
{
	va_list		args;

	va_start(args, format);

	va_end(args);
	return (0);
}
