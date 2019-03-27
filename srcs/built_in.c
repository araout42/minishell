/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:15:26 by araout            #+#    #+#             */
/*   Updated: 2019/03/27 18:31:15 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void			ft_unsetenv(char **opt, char **env)
{
	(void)opt;
	(void)env;
}

void			ft_cd(char **opt, char **env)
{
	(void)opt;
	(void)env;
}

static void		ft_exit(t_minishell **shell, char **opt, char **path)
{
	int		i;

	i = 0;
	if ((*shell)->path && (*shell)->cmp && (*shell)->cmp && (*shell)->env
			&& (*shell)->cmd && opt && path)
	{
	free_cmd((*shell)->path, &(*shell)->cmp);
	free_cmd((*shell)->env, &(*shell)->cmd);
	free_cmd(opt, path);
	}
	exit(0);
}

int				ft_built_in(char **opt, t_minishell **shell, char **path)
{
	if (!ft_strcmp("exit", opt[0]))
		ft_exit(shell, opt, path);
	else if (!ft_strcmp("setenv", opt[0]) &&
			((*shell)->env = ft_setenv(opt, (*shell)->env)))
		return (1);
	else if (!ft_strcmp("unsetenv", opt[0]))
	{
		ft_unsetenv(opt, (*shell)->env);
		return (1);
	}
	else if (!ft_strcmp("env", opt[0]))
	{
		ft_env((*shell)->env);
		return (1);
	}
	else if (!ft_strcmp("cd", opt[0]))
	{
		ft_cd(opt, (*shell)->env);
		return (1);
	}
	return (0);
}

void			ft_env(char **env)
{
	int		i;
	
	i = -1;
	while (env && env[++i])
		ft_printf("%s\n", env[i]);
}
