/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 23:03:49 by araout            #+#    #+#             */
/*   Updated: 2019/04/14 14:23:13 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"
#include "libft.h"

void	create_buffer(void *newbuff, size_t size, t_printf *pf)
{
	intmax_t	i;
	int			tmp;
	char		*nbuf;

	nbuf = newbuff;
	i = 0;
	tmp = 0;
	while ((64 - pf->buffi) < (int)size)
	{
		tmp = 64 - pf->buffi;
		ft_memcpy(&(pf->buff[pf->buffi]), &(nbuf[i]), tmp);
		size -= tmp;
		i += tmp;
		pf->buffi += tmp;
		pf->len += tmp;
		write(1, pf->buff, pf->buffi);
		pf->buffi = 0;
	}
	ft_memcpy(&(pf->buff[pf->buffi]), &(nbuf[i]), size);
	pf->buffi += size;
	pf->len += size;
}

void	put_width(t_printf *pf, int val)
{
	if (!pf->width)
		return ;
	pf->arg = ' ' | (pf->ff & ZERO);
	if (!val && !(pf->ff & MINUS))
	{
		while (pf->width--)
			create_buffer(&pf->arg, 1, pf);
	}
	else if (val && (pf->ff & MINUS))
	{
		while (pf->width--)
			create_buffer(&pf->arg, 1, pf);
	}
}

int		ft_printf(const char *format, ...)
{
	t_printf	pf;

	pf.format = (char*)format;
	pf.buffi = 0;
	va_start(pf.ap, format);
	while (*pf.format)
	{
		if (*pf.format == '%')
		{
			++pf.format;
			if (*pf.format)
				get_flag(&pf);
		}
		else
			create_buffer(pf.format, 1, &pf);
		++pf.format;
	}
	write(1, pf.buff, pf.buffi);
	va_end(pf.ap);
	return (pf.len);
}

void	no_valid_arg(t_printf *pf)
{
	pf->width -= 1;
	if (pf->width > 0)
	{
		put_width(pf, 0);
		create_buffer(pf->format, 1, pf);
		put_width(pf, 1);
		return ;
	}
	create_buffer(pf->format, 1, pf);
}
