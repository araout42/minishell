/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:09:59 by araout            #+#    #+#             */
/*   Updated: 2019/04/13 07:11:58 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_perms(char *path)
{
	struct stat	buf;
	int			flag;
	int			s;

	flag = 0;
	buf.st_mode = 0;
	s = stat(path, &buf);
	if (S_ISREG(buf.st_mode) && !access(path, X_OK))
		flag = 1;
	if (!access(path, F_OK) && access(path, X_OK))
		flag = -1;
	if (S_ISDIR(buf.st_mode))
		flag = -2;
	return (flag);
}

static int		throw_error2(t_minishell **shellstruct)
{
	if ((*shellstruct)->flag == -3)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	else if ((*shellstruct)->flag == -4)
	{
		ft_putstr_fd("cd: not a directory ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int				throw_error(t_minishell **shellstruct)
{
	if ((*shellstruct)->flag == -1)
	{
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd(" : Permission Denied\n", 2);
		return (-1);
	}
	else if ((*shellstruct)->flag == 0)
	{
		ft_putstr_fd("Cannot find : ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	else if ((*shellstruct)->flag == -2)
	{
		ft_putstr_fd("Cannot execute : ", 2);
		ft_putstr_fd((*shellstruct)->cmd, 2);
		ft_putstr_fd(" is a Directory.\n", 2);
	}
	else
		throw_error2(shellstruct);
	return (0);
}
