/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/03/13 05:49:42 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getpath(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*env)
	{
		tmp = ft_strsub(*env, 0, 5);
		if (ft_strcmp(tmp, "PATH=") == 0)
		{
			ft_strdel(&tmp);
			return (ft_strsplit(ft_strsub(*env, 5, ft_strlen(*env) - 5), ':'));
		}
		env++;
	}
	return (NULL);
}

int			try_exec(t_minishell *shellstruct, char *cmd)
{
	int		i;
	char *tmp;

	i = 0;

	while (shellstruct->path[i])
	{
		tmp = ft_strjoin(shellstruct->path[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!access(tmp, X_OK))
		{
			ft_printf("%s\n", tmp);
			fork();
			execve(tmp, NULL, NULL);
			ft_strdel(&tmp);
			return (i);
		}
		i++;
		ft_strdel(&tmp);
	}
	return (-1);
}

void	minishell(char **env)
{
	char			*cmd;
	t_minishell		*shellstruct;
	
	shellstruct = (t_minishell * )ft_memalloc(sizeof(*shellstruct));
	shellstruct->path = ft_getpath(env);
	while (1)
	{
		ft_printf("%>");
		if (get_next_line(0, &cmd) > 0)
		{
			try_exec(shellstruct, cmd);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}

