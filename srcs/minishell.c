/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/03/25 08:28:53 by araout           ###   ########.fr       */
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

	i = 0;
	while (env && *env)
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

static char		**get_env(char **env)
{
	int		i;
	char	**newenv;

	i = 0;
	if (env && *env)
	{
		while (env[i])
			i++;
		if (!(newenv = (char **)ft_memalloc(sizeof(newenv) * i)))
			return (NULL);
		i = -1;
		while (env[++i])
		{
			newenv[i] = ft_strdup(env[i]);
		}
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
	t_minishell		*shellstruct;
	int			i;
	int			flag;

	flag  = 0;
	i = 1;
	if (!(shellstruct = (t_minishell * )ft_memalloc(sizeof(*shellstruct))))
		return ;
	if ((shellstruct->env = get_env(env)) != NULL)
		shellstruct->env = set_var_env("SHLVL", sh_lvl(env), shellstruct->env);
	ft_printf("%%>");
	while ((i = get_next_line(0, &cmd)) > 0)
	{
		shellstruct->path = ft_getpath(shellstruct->env);
		try_exec(&shellstruct, ft_strtrim(cmd));
		ft_printf("%%>");
	}
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}
