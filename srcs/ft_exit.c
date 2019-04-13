/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:08:06 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:08:29 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_exit(t_minishell **shell, char **opt, char **path, char **t)
{
	int		i;

	i = 0;
	if (shell && *shell)
	{
		if (ft_strcmp(*t, "0"))
			free_cmd((*shell)->path, NULL);
		if ((*shell)->cmp)
			ft_strdel(&(*shell)->cmp);
		free_cmd((*shell)->env, &(*shell)->cmd);
		free_cmd(opt, path);
		ft_memdel((void *)shell);
	}
	ft_strdel(t);
	exit(0);
}
