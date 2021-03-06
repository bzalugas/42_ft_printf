/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzalugas <bzalugas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:21:40 by bzalugas          #+#    #+#             */
/*   Updated: 2022/01/22 16:46:29 by bzalugas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_char(char c, char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}
