/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:15:26 by araout            #+#    #+#             */
/*   Updated: 2019/04/10 05:04:47 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**dump_env_unset(char **env, int index)
{
	int		size;
	char	**new;
	int		i;
	int		j;


	size = 0;
	while(env[size])
		size++;
	if (!(new = (char **)ft_memalloc(sizeof(new) * (size) - 1)))
		return (NULL);
	new[size - 1] = NULL;
	i = -1;
	j = 0;
	while (env[++i] != NULL)
	{
		if (i != index)
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		ft_strdel(&env[i]);
	}
	ft_memdel((void *)&env);
	return (new);
}


char			**ft_unsetenv(char **opt, char **env)
{
	int		index;

	index = find_var(opt[1], env);
	if (env && env[index])
		env = dump_env_unset(env, index);
	else
		ft_putstr_fd("Unsetenv error : Cannot find Variable\n", 2);
	return (env);
}

void			ft_cd_home(t_minishell *shell)
{
	int		index;

	index = find_var("HOME", shell->env);
	if (shell->env[index])
	{
		shell->flag = check_perms(shell->env[index]+5);
		shell->cmd = shell->env[index]+5;
		if (shell->flag == -2)
		{
			if (access(shell->env[index]+5, X_OK))
				shell->flag = -3;
			else
				shell->flag = 1;
		}
		else if (shell->flag == -1)
			shell->flag = -4;
		throw_error(&shell);
		chdir(shell->env[index]+5);
	}
}

void			ft_cd_absolute(t_minishell *shell, char **opt)
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

void			ft_cd_relative(char **opt, char *tmp, char *c, t_minishell *s)
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

char			*ft_cd(char **opt, t_minishell shell, char *path, char	*c)
{
	t_minishell *tmpshell;

	if (!opt[1])
		ft_cd_home(&shell);
	if (opt && opt[1] && opt[1][0] != '/' && (tmpshell = &shell))
		ft_cd_relative(opt, NULL, c, tmpshell);
	else if (opt && opt[1] && 1 && (tmpshell = &shell))
		ft_cd_absolute(tmpshell, opt);
	return (getcwd(path, 1024));
}

static void		ft_exit(t_minishell **shell, char **opt, char **path, char **t)
{
	int		i;

	i = 0;
	ft_strdel(t);
	if (shell && *shell)
	{
		free_cmd((*shell)->path, &(*shell)->cmp);
		free_cmd((*shell)->env, &(*shell)->cmd);
		free_cmd(opt, path);
		ft_memdel((void *)shell);
	}
	exit(0);
}

int				ft_built_in(char **opt, t_minishell **shell, char **p, char **t)
{
	char		*tmp;

	tmp = NULL;
	if (!ft_strcmp("exit", opt[0]))
		ft_exit(shell, opt, p, t);
	else if (!ft_strcmp("setenv", opt[0]) &&
			((*shell)->env = ft_setenv(opt, (*shell)->env)))
		return (1);
	else if (!ft_strcmp("unsetenv", opt[0]))
	{
		(*shell)->env = ft_unsetenv(opt, (*shell)->env);
		return (1);
	}
	else if (!ft_strcmp("env", opt[0]) && (ft_env((*shell)->env)))
		return (1);
	else if (!ft_strcmp("cd", opt[0]))
	{
		tmp = getcwd(tmp, 1024);
		(*shell)->env = set_var_env("OLDPWD", tmp, (*shell)->env);
		ft_strdel(&tmp);
		tmp = ft_cd(opt, (**shell), NULL, NULL);
		(*shell)->env = set_var_env("PWD", tmp, (*shell)->env);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int				ft_env(char **env)
{
	int		i;
	
	i = -1;
	while (env && env[++i])
		ft_printf("%s\n", env[i]);
	return (i);
}
