/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:45:20 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:22:24 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			in_loop(t_minishell *shell, char *cmd)
{
	char	*tmp;

	if (cmd[0])
	{
		shell->path = ft_getpath(shell->env, NULL);
		if ((tmp = ft_strtrim(cmd)) == NULL)
			return ;
		ft_strdel(&cmd);
		if (ft_strlen(tmp))
			try_exec(&shell, &tmp, 0);
		ft_strdel(&tmp);
		free_cmd(shell->path, NULL);
		ft_printf("%%>");
	}
	else
		ft_printf("%%>");
	ft_strdel(&cmd);
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

	check = NULL;
	signal(SIGINT, catch_sigint);
	if ((shell = init_minishell(env)) == NULL)
		return ;
	i = 1;
	while ((i = get_next_line(0, &cmd)) > 0)
	{
		parse_cmd(&cmd, shell);
		in_loop(shell, cmd);
	}
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
