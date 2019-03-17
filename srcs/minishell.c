/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/03/17 08:17:36 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dump_env(char **env, char *to_add)
{
	char	**envdump;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env[i])
		i++;
	if (to_add)
	{
		if (!(envdump = (char **)ft_memalloc(sizeof(envdump) * i + 2)))
			return (NULL);
		envdump[i + 1] = to_add;
		envdump[i + 2] = NULL;
	}
	else
	{
		if (!(envdump = (char **)ft_memalloc(sizeof(envdump) * i + 1)))
			return (NULL);
		envdump[i + 1] = NULL;
	}
		j = -1;
	while (j <= i && env[++i])
		envdump[i] = ft_strdup(env[i]);
	return (envdump);
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
			return (ft_strsplit(ft_strsub(*env, 5, ft_strlen(*env) - 5), ':'));
		}
		env++;
	}
	return (NULL);
}

char		*ft_get_command(char *cmd)
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

char		*get_path(char *cmd, char *path)
{
	char	*tmp;
	char	*command;

	command = ft_get_command(cmd);
	path = ft_strjoin(path, "/");
	tmp = path;
	path = ft_strjoin(path, command);
	ft_strdel(&tmp);
	ft_strdel(&command);
	return (path);
}

int			free_cmd(char **opt, char **path)
{
	int		i;

	i = -1;
	while (opt[++i])
		ft_strdel(&opt[i]);
	if (path != NULL)
		ft_strdel(path);
	return (1);
}

char		**ft_setenv(char **opt, char **env)
{
	int		i;
	char	**tmp;
	char	*tmp2;
	char	*new_line;

	i = 0;
	new_line = ft_strjoin(opt[1], "=");
	tmp2 = new_line;
	new_line = ft_strjoin(new_line, opt[2]);
	ft_strdel(&tmp2);
	tmp = env;
	env = dump_env(env, new_line);
	free_cmd(tmp, NULL);
	return (env);
}

void		ft_unsetenv(char **opt, char **env)
{
	(void)opt;
	(void)env;
}

void	ft_cd(char **opt, char **env)
{
	(void)opt;
	(void)env;
	
}

int			execute_cmd(char **path, char *cmd, t_minishell *shell)
{
	char	**opt;
	int		fork_id;

	opt = ft_strsplit(cmd,  ' ');
	if (!access(*path, X_OK))
	{
		shell->flag = 1;
		fork_id = fork();
		if (fork_id == 0)
			execve(*path, opt, shell->env);
		else
			wait(NULL);
	}
	else if (!ft_strcmp("exit", opt[0]))
	{
		free_cmd(opt, path);
		exit(0);
	}
	else if (!ft_strcmp("setenv", opt[0]))
		shell->env = ft_setenv(opt, shell->env);
	else if (!ft_strcmp("unsetenv", opt[0]))
		ft_unsetenv(opt, shell->env);
	else if (1 && (shell->cmd = ft_strdup(opt[0])))
		return (0);
	return (1);
}

int			try_exec(t_minishell *shellstruct, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (((path = get_path(cmd, shellstruct->path[i])) != NULL))
	{
		shellstruct->flag = execute_cmd(&path, cmd, shellstruct);
		if (shellstruct->flag)
			break ;
		i++;
	}
	if (!shellstruct->flag)
	{
		ft_putstr_fd("Cannot execute : ", 2);
		ft_putstr_fd(shellstruct->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	return (-1);
}


void	minishell(char **env)
{
	char			*cmd;
	t_minishell		*shellstruct;
	
	shellstruct = (t_minishell * )ft_memalloc(sizeof(*shellstruct));
	shellstruct->path = ft_getpath(env);
	shellstruct->env = dump_env(env, NULL);
	while (1)
	{
		ft_printf("%%>");
		if (get_next_line(0, &cmd) > 0)
		{
			try_exec(shellstruct, cmd);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}

