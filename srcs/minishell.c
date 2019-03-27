/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/03/27 17:51:12 by araout           ###   ########.fr       */
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

char	**ft_getpath(char **env)
{
	int		i;
	char	*tmp;
	char	**ret;

	i = 0;
	if (!env && (ret = ft_memalloc(sizeof(env) * 2)))
	{
		*ret = ft_strdup("./");
		ret[1] = NULL;
		return (ret);
	}
	while (*env && (tmp = ft_strsub(*env, 0, 5)))
	{
		if (ft_strcmp(tmp, "PATH=") == 0 && ft_strdel(&tmp))
		{
			tmp = ft_strsub(*env, 5, ft_strlen(*env) - 5);
			ret = ft_split_str(tmp, ":");
			ft_strdel(&tmp);
			return (ret);
		}
		ft_strdel(&tmp);
		env++;
	}
	ft_strdel(&tmp);
	return (NULL);
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

void			minishell(char **env)
{
	char			*cmd;
	t_minishell		*shell;
	int				i;
	int				flag;
	char		*tmp;
	flag  = 0;
	i = 1;
	if (!(shell = (t_minishell * )ft_memalloc(sizeof(*shell))))
		return ;
	tmp = sh_lvl(env);
	if ((shell->env = get_env(env))
			&& !(shell->env = set_var_env("SHLVL", tmp, shell->env)))
			return ;
	if (ft_strcmp(tmp, "1"))
		ft_strdel(&tmp);
	ft_printf("%%>");
	while ((i = get_next_line(0, &cmd)) > 0)
	{
		shell->path = ft_getpath(shell->env);
		tmp = ft_strtrim(cmd);
		try_exec(&shell, tmp);
		free_cmd(shell->path, NULL);
		ft_strdel(&cmd);
		ft_strdel(&tmp);
		ft_printf("%%>");
	}
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}
