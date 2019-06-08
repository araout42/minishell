/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 01:14:58 by araout            #+#    #+#             */
/*   Updated: 2019/05/03 02:59:35 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsep(char **str, char *token)
{
	char	*begin;
	char	*end;

	if (!str)
		return (NULL);
	begin = *str;
	if (begin == NULL)
		return (NULL);
	end = begin + ft_strcspn(begin, token);
	if (*end)
	{
		*end++ = '\0';
		*str = end;
	}
	else
		*str = NULL;
	return (begin);
}
