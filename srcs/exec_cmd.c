/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:08:50 by araout            #+#    #+#             */
/*   Updated: 2019/03/25 10:18:51 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			check_perms(char *path)
{
	struct stat buf;

	stat(path, &buf);
	if (S_ISREG(buf.st_mode) && !access(path, X_OK))
		return (1);
	return (-1);
}

int			execute_cmd(char **path, char *cmd, t_minishell **shell)
{
	char	**opt;
	int		fork_id;
	int		flag;

	if (cmd[0])
		opt = ft_split_str(cmd,  " \t");
	else
		return (1);
	if ((flag = ft_built_in(opt, shell, path)))
		return (flag);
	else if ((flag = check_perms(*path)) != -1)
	{
		(*shell)->flag = 1;
		fork_id = fork();
		if (fork_id == 0)
			execve(*path, opt, (*shell)->env);
		else
			wait(NULL);
	}
	(*shell)->cmd = ft_strdup(opt[0]);
	return (flag);
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
			i++;
		}
		if ((*shellstruct)->flag != 1)
		{
			ft_putstr_fd("Cannot execute : ", 2);
			ft_putstr_fd((*shellstruct)->cmd, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
		(*shellstruct)->flag = execute_cmd(&cmd, cmd, shellstruct);
	return (-1);
}

int			free_cmd(char **opt, char **path)
{
	int		i;

	i = -1;
	while (opt[i])
		i++;
	while (i >= 0)
		ft_strdel(&opt[i--]);
	if (path != NULL)
		ft_strdel(path);
	return (1);
}

