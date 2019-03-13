/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 20:07:21 by mgheraie          #+#    #+#             */
/*   Updated: 2018/12/29 14:16:14 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(uintmax_t nb)
{
	int i;

	i = 0;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}
