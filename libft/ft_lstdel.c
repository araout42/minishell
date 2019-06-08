/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:08:03 by araout            #+#    #+#             */
/*   Updated: 2018/11/13 18:56:57 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void*, size_t))
{
	t_list *tmp;
	t_list *tofree;

	tmp = *alst;
	while (tmp)
	{
		tofree = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = tofree;
	}
	*alst = NULL;
}
