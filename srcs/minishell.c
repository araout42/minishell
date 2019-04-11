/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/04/11 10:42:55 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			sig_falg;

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
	char	*tmp;
	char	**ret;

	if (!env && (ret = ft_memalloc(sizeof(env) * 2)))
	{
		*ret = ft_strdup("./");
		ret[1] = NULL;
		return (ret);
	}
	while (*env && (tmp = ft_strsub(*env, 0, 5)))
	{
		if (ft_strcmp(tmp, "PATH=") == 0)
		{
			ft_strdel(&tmp);
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

void			catch_sigint(int fake)
{
	(void)fake;
	ft_printf("\n%%>");
}

void			catch_sigint2(int fake)
{
	(void)fake;
	ft_printf("\nINTERRUPTED\n");
}

t_minishell		*init_minishell(char **env)
{
	char		*tmp;
	t_minishell		*shell;
	
	if (!(shell = (t_minishell * )ft_memalloc(sizeof(*shell))))
		return (NULL);
	tmp = sh_lvl(env);
	if ((shell->env = get_env(env))
			&& !(shell->env = set_var_env("SHLVL", tmp, shell->env)))
		return (NULL);
	if (ft_strcmp(tmp, "1"))
		ft_strdel(&tmp);
	return (shell);
}

void			in_loop(t_minishell *shell, char *cmd)
{
	char	*tmp;

	if (cmd[0])
	{
		shell->path = ft_getpath(shell->env);
		tmp = ft_strtrim(cmd);
		ft_strdel(&cmd);
		try_exec(&shell, &tmp);
		ft_strdel(&tmp);
		free_cmd(shell->path, NULL);
		ft_printf("%%>");
	}
	else 
		ft_printf("%%>");
	ft_strdel(&cmd);
}

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
	if (sh->env && sh->env[id] &&ft_strlen(sh->env[id]) > ft_strlen(varname))
	{
		l_v = ft_strlen(sh->env[id] + ft_strlen(varname));
		if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * l_c + l_v)))
			return ;
		ft_strncpy(*cmd, old_cmd, i);
		ft_strcpy(*cmd + i, sh->env[id] + ft_strlen(varname));
		ft_strcpy(*cmd + (i + l_v), old_cmd + i + ft_strlen(varname));
	}
	else if (!(*cmd = (char *)ft_memalloc(sizeof(**cmd) * (l_c + (i - j)))))
			return ;
	else if (ft_strncpy(*cmd, old_cmd, i) || 1)
		ft_strcpy(*cmd + i, old_cmd + (i + ft_strlen(varname)));
	ft_strdel(&varname);
	ft_strdel(&old_cmd);
}

void			parse_dollar(char **cmd, int i, t_minishell *shell)
{
	int		j;

	j = i;
	while ((*cmd)[j] && (*cmd)[j] != ' ' && (*cmd)[j] != '\t')
		j++;
	if (j > i + 1)
		fill_cmd(cmd, i, j, shell);
}

void			parse_dollar_dollar(char **cmd, int i)
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

void			parse_tilde(char **cmd, int i, t_minishell *sh)
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
	if (sh->env && sh->env[index] && ft_strlen(sh->env[index]) > (ft_strlen(vname) + 1))
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

void			parse_cmd(char **cmd, t_minishell *shell)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd || !shell)
		return ;
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

void			minishell(char **env)
{
	t_minishell		*shell;
	int				i;
	char			*cmd;

	signal(SIGINT, catch_sigint);
	shell = init_minishell(env);
	i = 1;
	while ((i = get_next_line(0, &cmd)) > 0)
	{
		parse_cmd(&cmd, shell);
		in_loop(shell, cmd);
	}
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_printf("%%>");
	minishell(env);
}
