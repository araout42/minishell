/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:15:26 by araout            #+#    #+#             */
/*   Updated: 2019/03/24 07:46:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		ft_unsetenv(char **opt, char **env)
{
	(void)opt;
	(void)env;
}

void	ft_cd(char **opt, char **env)
{
	(void)opt;
	(void)env;
	
}

void		ft_env(char **env)
{
	int		i;
	
	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}
