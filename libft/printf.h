/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 23:01:37 by mgheraie          #+#    #+#             */
/*   Updated: 2019/04/14 15:00:37 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdint.h>
# include <stdarg.h>
# include "libft.h"

typedef	struct	s_printf
{
	int			len;
	int			width;
	int			precision;
	va_list		ap;
	int			fi;
	int			finalsize;
	char		buff[64];
	int			buffi;
	int			ff;
	char		arg;
	char		*format;
}				t_printf;

# define DIEZ			1
# define SPACE			2
# define PLUS			4
# define MINUS			8
# define ZERO			16
# define SHORT			32
# define CHAR			64
# define LONG			128
# define LONGLONG		256
# define ISPRECI		521
# define ISADDRESS		1024

void			create_buffer(void *newbuff, size_t size, t_printf *pf);
int				ft_printf(const char *format, ...);
void			get_flag(t_printf *pf);
void			ft_printf_itoa(intmax_t nb, int len, t_printf *pf);
void			printf_putchar(t_printf *pf);
uintmax_t		unsigned_int_flag(int flag, unsigned int arg);
void			printf_putaddr(t_printf *pf);
void			printf_putstr(t_printf *pf);
void			no_valid_arg(t_printf *pf);
void			put_width(t_printf *pf, int val);
char			*string_converter(char *ap, int conv);
void			ft_printf_itoa_base(uintmax_t nb, uintmax_t tmp,
			t_printf *pf, int base);
int				ft_is_flag(t_printf *pf);
int				ft_is_arg(t_printf *pf);
void			printf_putnbr(t_printf *pf);
void			printf_putunbr(int base, t_printf *pf);

#endif
