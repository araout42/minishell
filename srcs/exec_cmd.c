/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:08:50 by araout            #+#    #+#             */
/*   Updated: 2019/03/24 10:03:24 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			execute_cmd(char **path, char *cmd, t_minishell **shell)
{
	char	**opt;
	int		fork_id;

	opt = ft_split_str(cmd,  " \t");
	if (!access(*path, X_OK))
	{
		(*shell)->flag = 1;
		fork_id = fork();
		if (fork_id == 0)
			execve(*path, opt, (*shell)->env);
		else
			wait(NULL);
	}
	else if (!ft_strcmp("exit", opt[0]))
	{
		free_cmd(opt, path);
		exit(0);
	}
	else if (!ft_strcmp("setenv", opt[0]))
	{
		(*shell)->env = ft_setenv(opt, (*shell)->env);
	}
	else if (!ft_strcmp("unsetenv", opt[0]))
		ft_unsetenv(opt, (*shell)->env);
	else if (!ft_strcmp("env", opt[0]))
		ft_env((*shell)->env);
	else if (!ft_strcmp("cd", opt[0]))
		ft_cd(opt, (*shell)->env);
	else if (1 && ((*shell)->cmd = ft_strdup(opt[0])))
		return (0);
	return (1);
}

int			try_exec(t_minishell **shellstruct, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (((path = get_path(cmd, (*shellstruct)->path[i])) != NULL))
	{
		(*shellstruct)->flag = execute_cmd(&path, cmd, shellstruct);
		if ((*shellstruct)->flag)
			break ;
		i++;
	}
	if (!(*shellstruct)->flag)
	{
		ft_putstr_fd("Cannot execute : ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
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
			return (ft_split_str(ft_strsub(*env, 5, ft_strlen(*env) - 5), ":"));
		}
		env++;
	}
	return (NULL);
}

