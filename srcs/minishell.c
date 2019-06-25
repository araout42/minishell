/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/06/25 03:24:14 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			in_loop(t_minishell *shell, char **cmd)
{
	char	*tmp;
	int		j;
	char	**cut_cmd;

	j = -1;
	if (cmd && *cmd && **cmd)
	{
		cut_cmd = ft_split_str(*cmd, ";");
		while (cut_cmd[++j])
		{
			parse_cmd(&cut_cmd[j], shell);
			shell->path = ft_getpath(shell->env, NULL);
			if ((tmp = ft_strtrim(cut_cmd[j])) == NULL)
				return ;
			if (ft_strlen(tmp))
				try_exec(&shell, &tmp, 0);
			ft_strdel(&tmp);
			free_cmd(shell->path, NULL);
		}
		free_cmd(cut_cmd, NULL);
	}
	ft_strdel(cmd);
	ft_printf("%%>");
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

int my_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int			del_char(char **cmd, char *buf)
{
	int		i;

	i = -1;
	if (buf[0] == 127)
	{
		if (ft_strlen(*cmd))
		{
				tputs(tgetstr("le", NULL), 1, my_putchar);
				tputs(tgetstr("dc", NULL), 1, my_putchar);
			return (1);
		}
			return (1);
	}
	return (0);
}

int			is_tcap(char **cmd, t_minishell *shell, char *buf)
{
	char	tcap[3];

	tcap[2] = '\0';
	if (*buf == 27)
	{
		ft_printf("%d\n", '\t');
		read(0, tcap, 2);
		return (1);
	}
	else if (*buf == 9)
	{
		return (1);
	}
	else if (del_char(cmd, buf))
	{
		if (ft_strlen(*cmd))
			(*cmd)[ft_strlen(*cmd) - 1] = '\0';
		return (1);
	}
	return (0);
}

int			ft_eval_read_tcaps(char **cmd, t_minishell *shell, char *buf)
{
	char *tmp;

	if (!is_tcap(cmd, shell, buf))
	{
		write(1, buf, 1);
		if (cmd && *cmd)
		{
			tmp = *cmd;
			if (!(*cmd = ft_strjoin(*cmd, buf)))
				return (0);
			ft_strdel(&tmp);
		}
		else if (cmd && !*cmd)
		{
			if (!(*cmd = ft_strdup(buf)))
				return (0);
		}
	}
	return (1);
}

int			ft_read(char **cmd, t_minishell *shell)
{
	int		i;
	char	*tmp;
	char	buf[2];

	buf[1] = '\0';
	while (read(0, buf, 1) > 0 && *buf != '\n')
	{
		if (!ft_eval_read_tcaps(cmd, shell, buf))
		{
			write(1, "error reading cmd", 17);
			return (0);
		}
	}
	if (*buf == '\n')
		write(1, "\n", 1);
	return (1);
}

void			minishell(char **env)
{
	t_minishell		*shell;
	int				i;
	char			*cmd;
	char			*check;

	cmd = NULL;
	if ((shell = init_minishell(env)) == NULL)
		return ;
	i = 1;
	while ((i = ft_read(&cmd, shell)) > 0)
		in_loop(shell, &cmd);
	check = ft_strdup("0");
	ft_exit(&shell, NULL, &cmd, &check);
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGINT, catch_sigint);
	ft_printf("%%>");
	minishell(env);
}
