/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/08 18:47:11 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		get_flags(t_flags *flags, const char *format, va_list args)
{
	size_t	i;

	i = 0;
	while (format[i] && (ft_strchr(FLAGS, format[i]) || ft_isdigit(format[i])))
	{
		flags->minus |= format[i] == CONVERSIONS[0];
		flags->zero |= format[i] == CONVERSIONS[1];
		flags->dot |= format[i] == CONVERSIONS[2];
		flags->sharp |= format[i] == CONVERSIONS[3];
		flags->space |= format[i] == CONVERSIONS[4];
		flags->plus |= format[i] == CONVERSIONS[5];
		if (ft_isdigit(format[i]) && format[i] != '0')
		{
			//atoi the digit in right member depending on already entered flags
		}
	}
}

char		*get_conversion(const char *format, va_list args)
{
	t_flags	flags;

	//get flags

	//convert
	//process flags
	//return created str
}

t_buffer	*format_to_buffer(const char *format, va_list args)
{
	t_buffer	*buf;
	size_t		i;

	buf = NULL;
	i = 0;
	while (format[i])
	{
		if (ft_strchr(CONVERSIONS, format[i]))
		{
			buff_add_back(&buf, buff_new((char *)format, i));

		}
		i++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;

	va_start(args, format);

	va_end(args);
	return (0);
}
