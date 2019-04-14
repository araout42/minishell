/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/04/14 14:59:13 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void			in_loop(t_minishell *shell, char *cmd)
{
	char	*tmp;
	int		j;
	char	**cut_cmd;

	j = -1;
	if (cmd[0])
	{
		cut_cmd = ft_split_str(cmd, ";");
		ft_strdel(&cmd);
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

void			minishell(char **env)
{
	t_minishell		*shell;
	int				i;
	char			*cmd;
	char			*check;

	cmd = NULL;
	check = NULL;
	signal(SIGINT, catch_sigint);
	if ((shell = init_minishell(env)) == NULL)
		return ;
	i = 1;
	while ((i = get_next_line(0, &cmd)) > 0)
		in_loop(shell, cmd);
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
