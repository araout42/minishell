/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 23:07:16 by araout            #+#    #+#             */
/*   Updated: 2019/05/03 02:43:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int	ft_is_arg(t_printf *pf)
{
	if (*pf->format == 'd' || *pf->format == 'i' || *pf->format == 'o'
			|| *pf->format == 'x' || *pf->format == 'X' || *pf->format == 'u'
			|| *pf->format == 's' || *pf->format == 'p' || *pf->format == 'c'
			|| *pf->format == 'f')
		return (1);
	return (0);
}
