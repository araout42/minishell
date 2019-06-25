/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:03:17 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:05:20 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_cd_home(t_minishell *shell)
{
	int		index;

	index = find_var("HOME", shell->env);
	if (shell->env[index])
	{
		shell->flag = check_perms(shell->env[index] + 5);
		shell->cmd = shell->env[index] + 5;
		if (shell->flag == -2)
		{
			if (access(shell->env[index] + 5, X_OK))
				shell->flag = -3;
			else
				shell->flag = 1;
		}
		else if (shell->flag == -1)
			shell->flag = -4;
		throw_error(&shell);
		chdir(shell->env[index] + 5);
	}
}

static void		ft_cd_absolute(t_minishell *shell, char **opt)
{
	shell->flag = check_perms(opt[1]);
	shell->cmd = opt[1];
	if (shell->flag == -2)
	{
		if (access(opt[1], X_OK))
			shell->flag = -3;
		else
			shell->flag = 1;
	}
	else if (shell->flag == -1)
		shell->flag = -4;
	throw_error(&shell);
	chdir(opt[1]);
}

static void		ft_cd_relative(char **opt, char *tmp, char *c, t_minishell *s)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 1024);
	tmp = ft_strjoin(path, "/");
	c = ft_strjoin(tmp, opt[1]);
	s->flag = check_perms(c);
	s->cmd = opt[1];
	if (s->flag == -2)
	{
		if (access(c, X_OK))
			s->flag = -3;
		else
			s->flag = 1;
	}
	else if (s->flag == -1)
		s->flag = -4;
	throw_error(&s);
	chdir(c);
	ft_strdel(&path);
	ft_strdel(&tmp);
	ft_strdel(&c);
}

static void		cd_minest(t_minishell *shell)
{
	int		index;
	char	**tmp;

	index = find_var("OLDPWD", shell->env);
	tmp = (char **)ft_memalloc(sizeof(tmp) * 3);
	tmp[2] = NULL;
	tmp[0] = (char *)ft_memalloc(sizeof(**tmp) * 3);
	tmp[0][2] = '\0';
	ft_strcpy(tmp[0], "cd");
	if (shell->env[index])
		tmp[1] = ft_strdup(shell->env[index] + 7);
	else
	{
		tmp[1] = (char *)ft_memalloc(sizeof(char) * 2);
		tmp[1][1] = '\0';
		tmp[1][0] = '~';
		parse_cmd(&tmp[1], shell);
	}
	ft_cd_absolute(shell, tmp);
	free_cmd(tmp, NULL);
}

char			*ft_cd(char **opt, t_minishell shell, char *path, char *c)
{
	t_minishell	*tmpshell;

	if (!opt || !shell.env)
		return (NULL);
	if (opt[0] && !opt[1])
		ft_cd_home(&shell);
	else if (!(ft_strcmp(opt[1], "-")) && shell.env && (tmpshell = &shell))
		cd_minest(tmpshell);
	else if (opt && opt[1] && opt[1][0] != '/' && (tmpshell = &shell))
		ft_cd_relative(opt, NULL, c, tmpshell);
	else if (opt && opt[1] && 1 && (tmpshell = &shell))
		ft_cd_absolute(tmpshell, opt);
	return (getcwd(path, 1024));
}
