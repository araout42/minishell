/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:18:55 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:21:45 by araout           ###   ########.fr       */
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

char			**ft_getpath(char **env, char *tmp)
{
	char	**ret;

	if (!env && (ret = ft_memalloc(sizeof(env) * 2)))
	{
		ret[0] = ft_strdup("./");
		ret[1] = NULL;
		return (ret);
	}
	while (*env && (tmp = ft_strsub(*env, 0, 5)))
	{
		if (ft_strcmp(tmp, "PATH=") == 0)
		{
			ft_strdel(&tmp);
			tmp = ft_strsub(*env, 5, ft_strlen(*env) - 5);
			if (!(ret = ft_split_str(tmp, ":")))
				return (NULL);
			ft_strdel(&tmp);
			return (ret);
		}
		ft_strdel(&tmp);
		env++;
	}
	ft_strdel(&tmp);
	return (NULL);
}

char			*sh_lvl(char **env)
{
	int		shlvl;
	int		index;

	index = find_var("SHLVL", env);
	if (env && env[index])
	{
		shlvl = ft_atoi(&env[index][6]) + 1;
		return (ft_itoa(shlvl));
	}
	else
		return ("1");
}

static char		**get_env(char **env)
{
	int		i;
	char	**newenv;

	i = 0;
	if (env && *env)
	{
		while (env[i])
			i++;
		if (!(newenv = (char **)ft_memalloc(sizeof(char **) * (i + 1) + 1)))
			return (NULL);
		newenv[i] = NULL;
		i = -1;
		while (env[++i])
			newenv[i] = ft_strdup(env[i]);
	}
	else
		return (NULL);
	return (newenv);
}

t_minishell		*init_minishell(char **env)
{
	char			*tmp;
	t_minishell		*shell;

	if (!(shell = (t_minishell *)ft_memalloc(sizeof(*shell))))
		return (NULL);
	bzero((void *)shell, sizeof(*shell));
	shell->cmd = NULL;
	shell->path = NULL;
	tmp = sh_lvl(env);
	if ((shell->env = get_env(env))
			&& !(shell->env = set_var_env("SHLVL", tmp, shell->env)))
		return (NULL);
	if (ft_strcmp(tmp, "1"))
		ft_strdel(&tmp);
	return (shell);
}