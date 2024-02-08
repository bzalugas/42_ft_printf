/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:39:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/08 18:44:01 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CONVERSIONS "cspdiuxX%"
# define FLAGS "-0.# +"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

/*********************************** STRUCTS **********************************/

typedef struct s_buffer	t_buffer;
typedef struct s_flags	t_flags;

struct s_flags
{
	unsigned char	minus:1;
	unsigned char	zero:1;
	unsigned char	dot:1;
	unsigned char	sharp:1;
	unsigned char	space:1;
	unsigned char	plus:1;
	unsigned char	min_width:1; // ?
	int				width;
	int				pad;
};

struct s_buffer
{
	char		*str;
	size_t		len;
	t_buffer	*next;
};

/****************************** BUFFER FUNCTIONS ******************************/

t_buffer	*buff_new(char	*str, size_t len);
void		buff_add_back(t_buffer **buff, t_buffer *new);
void		buff_clear(t_buffer **buff);

/****************************** UTILS FUNCTIONS *******************************/

char		*ft_strchr(const char *s, int c);
int			ft_isdigit(int c);

#endif
