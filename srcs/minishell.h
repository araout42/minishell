/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 04:46:00 by araout            #+#    #+#             */
/*   Updated: 2019/03/25 09:39:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_minishell
{
	char	*cmp;
	char	**path;
	char	**env;
	char	*cmd;
	int		flag;
} t_minishell;

int			ft_built_in(char **opt, t_minishell **shell, char **path);
char		**ft_getpath(char **env);
char		*ft_get_command(char *cmd);
int			execute_cmd(char **path, char *cmd, t_minishell **shell);
int			try_exec(t_minishell **shellstruct, char *cmd);
int			free_cmd(char **opt, char **path);
char		**ft_getpath(char **env);
void		ft_cd(char **opt, char **env);
void		ft_unsetenv(char **opt, char **env);
char		**ft_setenv(char **opt, char **env);
char		*get_path(char *cmd, char *path);
void		ft_env(char **env);
char		**ft_setenv(char **opt, char **env);
char		**set_var_env(char *varname, char *value, char **env);
int			find_var(char *varname, char **env);
#endif
