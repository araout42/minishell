/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/03/24 09:50:13 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_get_command(char *cmd)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * i);
	j = -1;
	while (j < i && cmd[++j] && cmd[j] != ' ')
		ret[j] = cmd[j];
	ret[j] = '\0';
	return (ret);
}

char			*get_path(char *cmd, char *path)
{
	char	*tmp;
	char	*command;

	command = ft_get_command(cmd);
	path = ft_strjoin(path, "/");
	tmp = path;
	path = ft_strjoin(path, command);
	ft_strdel(&tmp);
	ft_strdel(&command);
	return (path);
}

static char		**get_env(char **env)
{
	int		i;
	char	**newenv;

	i = 0;
	if (env)
	{
		while (env[i])
			i++;
		if (!(newenv = (char **)ft_memalloc(sizeof(newenv) * i)))
			return (NULL);
		i = -1;
		while (env[++i])
			newenv[i] = ft_strdup(env[i]);
	}
	else
		return (NULL);
	return (newenv);
}

void			minishell(char **env)
{
	char			*cmd;
	t_minishell		*shellstruct;
	int			i;
	int			flag;

	flag  = 0;
	i = 1;
	if (!(shellstruct = (t_minishell * )ft_memalloc(sizeof(*shellstruct))))
		return ;
	shellstruct->path = ft_getpath(env);
	shellstruct->env = get_env(env);
	ft_printf("%%>");
	while ((i = get_next_line(0, &cmd)) > 0)
	{
		try_exec(&shellstruct, ft_strtrim(cmd));
		ft_printf("%%>");
	}
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}
