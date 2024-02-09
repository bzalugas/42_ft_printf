/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:39:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 06:38:39 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "-0.# +*"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

/*********************************** STRUCTS **********************************/

typedef struct s_buffer	t_buffer;
typedef struct s_flags	t_flags;

typedef enum e_type
{
	LIT,
	CHAR,
	STR,
	INT,
	UINT,
	PTR,
	PERCENT
}			t_type;

struct s_flags
{
	unsigned char	minus:1;
	unsigned char	zero:1;
	unsigned char	dot:1;
	unsigned char	sharp:1;
	unsigned char	space:1;
	unsigned char	plus:1;
	int				width; // for min_width, minus (if width set but not minus,
						   // this is for min_width)
	int				pad; // for dot, zero
};

struct s_buffer
{
	t_type		type;
	size_t		len;
	void		*content;
	t_buffer	*next;
};

/****************************** BUFFER FUNCTIONS ******************************/

t_buffer	*buff_new(void *content, size_t len, t_type type);
void		buff_add_back(t_buffer **buff, t_buffer *new);
void		*buff_clear(t_buffer **buff);

/****************************** UTILS FUNCTIONS *******************************/

t_flags	*flags_init(void);

/********************************* FT_PRINTF **********************************/

int	ft_printf(const char *format, ...);

#endif
