/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/05/31 07:14:19 by araout           ###   ########.fr       */
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

int			ft_read(char **cmd)
{
	int		i;
	char	*tmp;
	char	buf[2];

	buf[1] = '\0';
	while (read(0, buf, 1) > 0 && *buf != '\n')
	{
		if (buf[0] != 27)
		{
			if (cmd && *cmd)
			{
				tmp = *cmd;
				if (!(*cmd = ft_strjoin(*cmd, buf)))
					return (0);
				ft_strdel(&tmp);
			}
			else if (cmd && !*cmd)
			{
				if (!( *cmd = ft_strdup(buf)))
					return (0);
			}
		}
		else 
		{
			tputs(tgoto(tgetstr("ll", NULL), 0, 0), 1, &my_putchar);
		}
	}
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
	while ((i = ft_read(&cmd)) > 0)
		in_loop(shell, &cmd);
	check = ft_strdup("0");
	ft_exit(&shell, NULL, &cmd, &check);
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_printf("%%>");
	
	minishell(env);
}
