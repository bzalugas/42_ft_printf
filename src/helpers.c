/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:48:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/16 23:23:32 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/* Helper for int/uint conversions */

bool	get_int_uint_adds(char **sp, char **zer, t_flags *f)
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

bool	get_hex_adds(char **sp, char **zer, t_flags *f)
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