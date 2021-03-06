/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzalugas <bzalugas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:05:28 by bzalugas          #+#    #+#             */
/*   Updated: 2022/02/05 10:36:15 by bzalugas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pointer_to_hexa(unsigned long p, int upper_case)
{
	char	*pointer;
	char	*hexa;

	pointer = ft_utoa(p);
	hexa = NULL;
	if (upper_case)
		hexa = ft_base_convert(pointer, "0123456789", "0123456789ABCDEF");
	else
		hexa = ft_base_convert(pointer, "0123456789", "0123456789abcdef");
	free(pointer);
	return (hexa);
}

void	handle_unsigned(unsigned n, t_flags *flags, t_buffer *buf)
{
	char	*num;

	num = ft_utoa(n);
	format_num(num, flags, buf);
	if (num)
		free(num);
}

void	handle_decimal(int n, t_flags *flags, t_buffer *buf)
{
	char	*num;

	num = ft_itoa(n);
	format_num(num, flags, buf);
	if (num)
		free(num);
}

void	handle_hexa(unsigned int n, t_flags *flags, t_buffer *buf)
{
	char	*hex;

	hex = pointer_to_hexa(n, (flags->conversion - 'x'));
	format_num(hex, flags, buf);
	if (hex)
		free(hex);
}

void	handle_pointer(unsigned long p, t_flags *flags, t_buffer *buf)
{
	char		*hexa;
	char		*pre;
	size_t		len;

	if (OS & LINUX && p == 0)
	{
		hexa = ft_strdup("(nil)");
		pre = "";
	}
	else
	{
		pre = "0x";
		hexa = pointer_to_hexa(p, 0);
	}
	hexa = ft_strjoin_free(pre, hexa, 0, 1);
	len = ft_strlen(hexa);
	if (flags->min_field && flags->padding > len)
		len += buffer_add_chars(buf, ' ', flags->padding - len);
	buffer_add_str(buf, hexa, 0, -1);
	if (flags->minus && flags->padding > len)
		len += buffer_add_chars(buf, ' ', flags->padding - len);
	free(hexa);
}
