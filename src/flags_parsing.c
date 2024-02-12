/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 07:57:58 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/12 13:04:01 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_flags	*flags_init(void)
{
	t_flags	*new;

	new = (t_flags *)malloc(sizeof(t_flags));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_flags));
	return (new);
}

static int	flags_handle_star(char *str, size_t *i, va_list args)
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

static void	flags_from_char(t_flags *flags, char c)
{
	flags->minus |= c == '-';
	flags->zero |= c == '0';
	flags->zero &= !flags->minus;
	flags->dot |= c == '.';
	flags->sharp |= c == '#';
	flags->space |= c == ' ';
	flags->plus |= c == '+';
}

void	flags_get(t_flags **flags, char *str, size_t *i, va_list args)
{
	*flags = flags_init();
	// Abort when same flag multiple times ?
	while (str[*i] && (ft_strchr(FLAGS, str[*i]) || ft_isdigit(str[*i])))
	{
		flags_from_char(*flags, str[*i]);
		if (str[*i] == '*' && (*flags)->dot)
			(*flags)->pad = flags_handle_star(str, i, args);
		else if (str[*i] == '*')
			(*flags)->width = flags_handle_star(str, i, args);
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
