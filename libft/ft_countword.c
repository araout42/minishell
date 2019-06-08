/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:01:25 by araout            #+#    #+#             */
/*   Updated: 2018/11/15 11:01:55 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countword(const char *s, char c)
{
	int i;
	int j;
	int boole;

	i = 0;
	j = 0;
	boole = 0;
	while (s[i])
	{
		if (boole == 1 && s[i] == c)
			boole = 0;
		if (boole == 0 && s[i] != c)
		{
			j++;
			boole = 1;
		}
		i++;
	}
	return (j);
}
