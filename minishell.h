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
# include "libft.h"
# include <sys/stat.h>
# define MAX_PATH_LENGTH 4096
// # define WHITE_SPACE(a) (a == ' ' || a == '\t' || a == '\v' || a == '\r')

typedef struct	s_minfo
{
	char	**env;
	char	*home;
	char	*env_path;
	char	**pre_path;//

	char	**av;//from input line
	int		ac;
	char	*cmd;//
	char	*cmd_path;//
	char	*bcmd;
}				t_minfo;


//get_info.c
int		get_info(int ac, char **av, char **env, t_minfo *info);
void	handle_env_path(t_minfo *info);
void	ck_cmd(t_minfo *info);
void	add_cmd(char *pre, char *cmd, char **path);
int		copy_env(char **env, t_minfo *info);


//minishell.c
int		minishell(t_minfo *info);
char	*ck_buildin_cmd(t_minfo *info);


//free.c
void	deep_free(char **dst);


//parse_line.c
int		get_av(char **av, t_minfo *info);
void	parse_line(t_minfo *info, char *line);
char	**handle_qoated(char *line);

//handle_quotes.c
void	change_space(char *line);
void	refill_space(char *av);
int			line_wordcount(char *str);
char		**line_split(char const *s);

#endif

// this is  some   test with "quoted text  nside it"   blablabla
// 00this0is00some000test0with0"quoted text  nside it"000blablabla

// ~ -> 
// echo ~	
//c == ' ' || line[i] == '\t' || line[i] == '\v' || line[i] == '\r'