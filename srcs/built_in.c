/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 05:15:26 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:33:58 by araout           ###   ########.fr       */
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
	while (env[size])
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

int				ft_built_in2(char **opt, t_minishell **sh)
{
	char		*tmp;
	char		*oldpwd;
	int			i;

	i = 0;
	tmp = NULL;
	if (!ft_strcmp("cd", opt[0]))
	{
		oldpwd = getcwd(tmp, 1024);
		tmp = ft_cd(opt, (**sh), NULL, NULL);
		(*sh)->env = set_var_env("OLDPWD", oldpwd, (*sh)->env);
		(*sh)->env = set_var_env("PWD", tmp, (*sh)->env);
		ft_strdel(&tmp);
		ft_strdel(&oldpwd);
		return (1);
	}
	else if (!ft_strcmp("echo", opt[0]))
	{
		while (opt[++i])
			ft_printf("%s ", opt[i]);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

int				ft_built_in(char **opt, t_minishell **shell, char **p, char **t)
{
	int		flag;

	flag = 0;
	if (!ft_strcmp("exit", opt[0]) && (flag = 1))
		ft_exit(shell, opt, p, t);
	else if (!ft_strcmp("setenv", opt[0]) && (flag = 1))
		(*shell)->env = ft_setenv(opt, (*shell)->env);
	else if (!ft_strcmp("unsetenv", opt[0]) && (flag = 1))
		(*shell)->env = ft_unsetenv(opt, (*shell)->env);
	else if (!ft_strcmp("env", opt[0]) && (flag = 1))
		ft_env((*shell)->env);
	else
		((flag = ft_built_in2(opt, shell)));
	return (flag);
}

int				ft_env(char **env)
{
	int		i;

	i = -1;
	while (env && env[++i])
		ft_printf("%s\n", env[i]);
	return (i);
}
