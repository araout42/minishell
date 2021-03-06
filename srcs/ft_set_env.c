/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 07:31:23 by araout            #+#    #+#             */
/*   Updated: 2019/06/17 06:16:31 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_var(char *s1, char *s2)
{
	int		i;

	i = 0;
	s2 = ft_strjoin(s2, "=");
	while (s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == s2[i])
	{
		ft_strdel(&s2);
		return (1);
	}
	ft_strdel(&s2);
	return (0);
}

int				find_var(char *varname, char **env)
{
	int		i;

	i = 0;
	if (!env || !env[i])
		return (i);
	while (env && env[i] && !is_var(env[i], varname))
		i++;
	return (i);
}

char			**dump_env(char **env, int size)
{
	int		i;
	char	**new;

	if (env == NULL)
	{
		if (!(new = (char **)ft_memalloc(sizeof(new) * 2)))
			return (NULL);
		return (new);
	}
	if (!(new = (char **)ft_memalloc(sizeof(new) * (size + 1))))
		return (NULL);
	new[size] = NULL;
	i = -1;
	while (env && env[++i])
	{
		new[i] = ft_strdup(env[i]);
		ft_strdel(&env[i]);
	}
	ft_memdel((void *)&env);
	return (new);
}

char			**set_var_env(char *varname, char *value, char **env)
{
	char		*tmp;
	int			index;

	index = find_var(varname, env);
	if (!(tmp = ft_strjoin(varname, "=")))
		return (NULL);
	if (env && env[index])
	{
		ft_strdel(&env[index]);
		if (!value)
			env[index] = tmp;
		else if ((env[index] = ft_strjoin(tmp, value)) || 1)
			ft_strdel(&tmp);
	}
	else
	{
		env = dump_env(env, index + 1);
		if (!value)
			env[index] = tmp;
		else if ((env[index] = ft_strjoin(tmp, value)) || 1)
			ft_strdel(&tmp);
	}
	return (env);
}

char			**ft_setenv(char **opt, char **env)
{
	char	**newenv;

	if (!opt || !opt[1] || !opt[2])
	{
		ft_putstr_fd("setenv error: 2 argument required\n", 2);
		return (env);
	}
	else if (opt[3])
	{
		ft_putstr_fd("setenv error: Takes only 2 arguments\n", 2);
		return (env);
	}
	if (!env)
		newenv = set_var_env(opt[1], opt[2], NULL);
	newenv = set_var_env(opt[1], opt[2], env);
	return (newenv);
}
