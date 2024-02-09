/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:39:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/02/09 19:27:24 by bazaluga         ###   ########.fr       */
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

/* width is used for min_width & minus flags
 * pad for dot & 0 flags
 * if width set but minus off, width is for min_width */

typedef struct s_flags
{
	unsigned char	minus:1;
	unsigned char	zero:1;
	unsigned char	dot:1;
	unsigned char	sharp:1;
	unsigned char	space:1;
	unsigned char	plus:1;
	int				width;
	int				pad;
}				t_flags;

typedef struct s_buffer
{
	t_type			type;
	size_t			len;
	void			*content;
	struct s_buffer	*next;
}				t_buffer;

/****************************** BUFFER FUNCTIONS ******************************/

t_buffer	*buff_new(t_type type, size_t len, void *content);
void		buff_add_back(t_buffer **buff, t_buffer *new);
void		*buff_clear(t_buffer **buff);
size_t		buff_update_len(size_t to_add);

/************************* FLAGS PARSING FUNCTIONS ****************************/

void		get_flags(t_flags **flags, char *str, size_t *i, va_list args);

/****************************** UTILS FUNCTIONS *******************************/

t_flags		*flags_init(void);

/********************************* FT_PRINTF **********************************/

int			ft_printf(const char *format, ...);

#endif
