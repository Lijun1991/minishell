/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:26:37 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 21:26:39 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/stat.h>

# define MAX_PATH_LENGTH 4096

typedef struct	s_minfo
{
	char	**env;
	char	*home;
	char	*env_path;
	char	**pre_path;//

	char	**av;
	int		ac;
	char	*cmd;//
	char	*cmd_path;//
	char	*bcmd;
}				t_minfo;

int		get_info(int ac, char **av, char **env, t_minfo *info);
void	handle_env_path(t_minfo *info);
void	ck_cmd(t_minfo *info);
void	add_cmd(char *pre, char *cmd, char **path);
int		copy_env(char **env, t_minfo *info);
int		get_av(char **av, t_minfo *info);

int		minishell(t_minfo *info);
char	*ck_buildin_cmd(t_minfo *info);

void	deep_free(char **dst);
#endif