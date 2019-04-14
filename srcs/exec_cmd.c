/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:08:50 by araout            #+#    #+#             */
/*   Updated: 2019/04/14 11:19:37 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_path(char *cmd, char *path)
{
	char	*tmp;
	char	*command;

	command = ft_get_command(cmd);
	if (!(path = ft_strjoin(path, "/")))
	{
		ft_strdel(&command);
		return (NULL);
	}
	tmp = path;
	if (!(path = ft_strjoin(path, command)))
	{
		ft_strdel(&command);
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	ft_strdel(&command);
	return (path);
}

int				execute_cmd(char **path, char **cmd, t_minishell **shell)
{
	char	**opt;
	int		fork_id;
	int		flag;

	if (cmd[0])
		opt = ft_split_str(*cmd, " \t");
	else
		return (1);
	if ((flag = ft_built_in(opt, shell, path, cmd)))
	{
		free_cmd(opt, NULL);
		return (flag);
	}
	else if ((flag = check_perms(*path)) == 1)
	{
		signal(SIGINT, catch_sigint2);
		if (!(fork_id = fork()) && fork_id == 0)
			execve(*path, opt, (*shell)->env);
		else
			wait(NULL);
		signal(SIGINT, catch_sigint);
	}
	(*shell)->cmd = ft_strdup(opt[0]);
	free_cmd(opt, NULL);
	return (flag);
}

void			absolute_path_execute(char **cmd, t_minishell **shell)
{
	char	**opt;

	opt = ft_split_str(*cmd, "\t ");
	(*shell)->flag = execute_cmd(opt, cmd, shell);
	free_cmd(opt, NULL);
}

int				try_exec(t_minishell **shellstruct, char **cmd, int i)
{
	char	*path;

	if ((*shellstruct)->path && (*cmd)[0] != '/' && (*cmd)[0] != '.')
	{
		while (((path = get_path(*cmd, (*shellstruct)->path[i])) != NULL))
		{
			if ((*shellstruct)->cmd)
				ft_strdel(&(*shellstruct)->cmd);
			(*shellstruct)->flag = execute_cmd(&path, cmd, shellstruct);
			if ((*shellstruct)->flag == 1)
				break ;
			else if ((*shellstruct)->flag == -1)
				break ;
			i++;
			ft_strdel(&path);
		}
		ft_strdel(&path);
	}
	else
		absolute_path_execute(cmd, shellstruct);
	throw_error(shellstruct);
	if ((*shellstruct)->cmd)
		ft_strdel(&(*shellstruct)->cmd);
	return (-1);
}

int				free_cmd(char **opt, char **path)
{
	int		i;

	i = -1;
	while (opt && opt[++i])
		ft_strdel(&opt[i]);
	free((void *)opt);
	if (path != NULL)
		ft_strdel(path);
	return (1);
}
