/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 17:11:53 by araout            #+#    #+#             */
/*   Updated: 2018/12/29 14:46:37 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_joinchar(char *s, char c)
{
	int		i;
	char	*res;

	if (!(res = ft_strnew(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	i++;
	res[i] = '\0';
	ft_strdel(&s);
	return (res);
}
