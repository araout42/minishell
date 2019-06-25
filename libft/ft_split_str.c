/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 22:35:51 by araout            #+#    #+#             */
/*   Updated: 2019/03/24 10:04:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_is_alpha(char c, char *s)
{
	int		i;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	if (i == (int)ft_strlen(s))
		return (1);
	return (0);
}

int			ft_getword(char *str, char *s)
{
	int		i;
	int		wordcount;

	i = 0;
	wordcount = 0;
	if (ft_is_alpha(str[0], s))
		wordcount = 1;
	while (str[i + 1])
	{
		while (ft_is_alpha(str[i + 1], s) && !(ft_is_alpha(str[i], s)))
		{
			wordcount++;
			i++;
		}
		i++;
	}
	return (wordcount);
}

char		*ft_getstring(char *str, int *b, char *s)
{
	int		i;
	int		z;
	char	*res;
	int		findumonde;

	z = *b;
	i = 0;
	findumonde = 0;
	while (!(ft_is_alpha(str[z], s) && str[z]))
		z++;
	while (ft_is_alpha(str[z], s) && str[z])
	{
		z++;
		i++;
	}
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (z - i < z)
		res[findumonde++] = str[z - i--];
	res[findumonde] = '\0';
	*b = z;
	return (res);
}

char		**ft_split_str(char *str, char *tosplit)
{
	char	**tab;
	int		i;
	int		count;
	int		b;

	b = 0;
	count = ft_getword(str, tosplit);
	i = 0;
	if (!(tab = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (i < count)
		tab[i++] = ft_getstring(str, &b, tosplit);
	tab[i] = 0;
	return (tab);
}
