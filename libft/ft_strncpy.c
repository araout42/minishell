/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:49:52 by araout            #+#    #+#             */
/*   Updated: 2018/11/08 15:15:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	c;
	int		i;

	i = 0;
	c = src[i];
	while (n--)
	{
		if (c != '\0')
			c = src[i];
		dest[i] = c;
		i++;
	}
	return (dest);
}
