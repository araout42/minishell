/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:13:51 by araout            #+#    #+#             */
/*   Updated: 2019/04/14 11:50:19 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			fill_cmd(char **cmd, int i, int j, t_minishell *sh)
{
	size_t	l_v;
	size_t	l_c;
	char	*varname;
	int		id;
	char	*old_cmd;

	old_cmd = *cmd;
	varname = ft_strsub(*cmd, i, j - i);
	id = find_var(varname + 1, sh->env);
	l_c = ft_strlen(*cmd);
	if (sh->env && sh->env[id] && ft_strlen(sh->env[id]) > ft_strlen(varname))
	{
		l_v = ft_strlen(sh->env[id] + ft_strlen(varname));
		if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * l_c + l_v)))
			return ;
		ft_strncpy(*cmd, old_cmd, i);
		ft_strcpy(*cmd + i, sh->env[id] + ft_strlen(varname));
		ft_strcpy(*cmd + (i + l_v), old_cmd + i + ft_strlen(varname));
	}
	else if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * (1 + l_c + (i - j)))))
		return ;
	else if (ft_strncpy(*cmd, old_cmd, i) || 1)
		ft_strcpy(*cmd + i, old_cmd + (i + ft_strlen(varname)));
	ft_strdel(&varname);
	ft_strdel(&old_cmd);
}

static void		parse_dollar_dollar(char **cmd, int i)
{
	pid_t	pid;
	char	*pidstr;
	int		len;
	char	*tmp;

	tmp = *cmd;
	pid = getpid();
	pidstr = ft_itoa(pid);
	len = ft_strlen(*cmd) + ft_strlen(pidstr) - 2;
	if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * len)))
		return ;
	ft_strncpy(*cmd, tmp, i);
	ft_strcpy(*cmd + i, pidstr);
	ft_strcpy(*cmd + (i + ft_strlen(pidstr)), tmp + i + 2);
	ft_strdel(&tmp);
	ft_strdel(&pidstr);
}

static void		parse_tilde(char **cmd, int i, t_minishell *sh)
{
	char		*tmp;
	char		vname[5];
	int			index;
	int			l_v;
	int			l_c;

	ft_strcpy((char *)vname, "HOME");
	tmp = *cmd;
	index = find_var(vname, sh->env);
	l_c = ft_strlen(*cmd);
	if (sh->env && sh->env[index]
			&& ft_strlen(sh->env[index]) > (ft_strlen(vname) + 1))
	{
		l_v = ft_strlen(sh->env[index] + ft_strlen(vname) + 1);
		if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * (l_c + l_v - 1))))
			return ;
		ft_strncpy(*cmd, tmp, i);
		ft_strcpy(*cmd + i, sh->env[index] + (ft_strlen(vname) + 1));
		ft_strcpy(*cmd + (i + l_v), tmp + (i + 1));
	}
	else if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * (l_c + 1))))
		return ;
	else if (ft_strncpy(*cmd, tmp, i) || 1)
		ft_strcpy(*cmd + i, tmp + (i + 1));
	ft_strdel(&tmp);
}

static void		parse_dqote(char **cmd)
{
	int		i;
	int		count;
	char	*tmp;
	int		j;

	tmp = *cmd;
	i = -1;
	count = 0;
	j = 0;
	while ((*cmd)[++i])
	{
		if ((*cmd)[i] == '"')
			count++;
	}
	if (!(*cmd = (char *)ft_memalloc(sizeof(char) * (ft_strlen(tmp) - count))))
		return ;
	(*cmd)[(ft_strlen(tmp) - count)] = '\0';
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] != '"' && ((*cmd)[j] = tmp[i]))
			j++;
	}
	ft_strdel(&tmp);
}

void			parse_cmd(char **cmd, t_minishell *shell)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd || !shell)
		return ;
	if (ft_strchr((*cmd), '"'))
		parse_dqote(cmd);
	while (((*cmd)[i] && (*cmd)[i + 1]) || (*cmd)[i] == '~')
	{
		if ((*cmd)[i] == '$' && (*cmd)[i + 1] != ' ' && (*cmd)[i + 1] != '\t')
		{
			if (((*cmd)[i] == '$' && (*cmd)[i + 1] == '$'))
				parse_dollar_dollar(cmd, i);
			else
				parse_dollar(cmd, i, shell);
		}
		else if ((*cmd)[i] == '~')
			parse_tilde(cmd, i, shell);
		i++;
	}
}
