/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:08:50 by araout            #+#    #+#             */
/*   Updated: 2019/03/27 18:52:32 by araout           ###   ########.fr       */
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

int			check_perms(char *path)
{
	struct	stat buf;
	int		flag;
	int		s;

	flag = 0;
	buf.st_mode = 0;
	s = stat(path, &buf);
	if (S_ISREG(buf.st_mode) && !access(path, X_OK))
		flag = 1;
	if (!access(path, F_OK) && access(path, X_OK))
		flag = -1;
	if (S_ISDIR(buf.st_mode))
		flag = -2;
	return (flag);
}

int			execute_cmd(char **path, char *cmd, t_minishell **shell)
{
	char	**opt;
	int		fork_id;
	int		flag;

	if ((*shell)->cmd)
		ft_strdel(&(*shell)->cmd);
	if (cmd[0])
		opt = ft_split_str(cmd,  " \t");
	else
		return (1);
	if ((flag = ft_built_in(opt, shell, path)))
	{
		free_cmd(opt, NULL);
		return (flag);
	}
	else if ((flag = check_perms(*path)) == 1)
	{
		if (!(fork_id = fork()) && fork_id == 0)
			execve(*path, opt, (*shell)->env);
		else
			wait(NULL);
	}
	(*shell)->cmd = ft_strdup(opt[0]);
	free_cmd(opt, NULL);
	return (flag);
}

int			throw_error(t_minishell **shellstruct)
{
	if ((*shellstruct)->flag == -1)
	{
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd(" : Permission Denied\n", 2);
		return (-1);
	}
	else if ((*shellstruct)->flag == 0)
	{
		ft_putstr_fd("Cannot find : ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	else if ((*shellstruct)->flag == -2)
	{
		ft_putstr_fd("Cannot execute : ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd(" is a Directory.\n", 2);
	}
	return (0);
}

int			try_exec(t_minishell **shellstruct, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if ((*shellstruct)->path && cmd[0] != '/' && cmd[0] != '.')
	{
		while (((path = get_path(cmd, (*shellstruct)->path[i])) != NULL))
		{
			(*shellstruct)->flag = execute_cmd(&path, cmd, shellstruct);
			if ((*shellstruct)->flag == 1)
				break ;
			else if ((*shellstruct)->flag == -1 && throw_error(shellstruct))
				break ;
			i++;
			ft_strdel(&path);
		}
		throw_error(shellstruct);
		ft_strdel(&path);
	}
	else
	{
		(*shellstruct)->flag = execute_cmd(&cmd, cmd, shellstruct);
		throw_error(shellstruct);
	}
	return (-1);
}

int			free_cmd(char **opt, char **path)
{
	int		i;

	i = -1;
	while (opt && opt[++i])
		ft_strdel(&opt[i]);
	free((void **)opt);
	if (path != NULL)
		ft_strdel(path);
	return (1);
}

