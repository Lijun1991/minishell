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
# include <dirent.h>
# define MAX_PATH_LENGTH 4096
// # define WHITE_SPACE(a) (a == ' ' || a == '\t' || a == '\v' || a == '\r')

typedef struct	s_minfo
{
	char	**env;
	char	**cmd_env;
	char	*home;
	char	*env_path;
	char	**pre_path;//from env path:

	char	**av;//from input line
	char	*cmd;//
	char	*cmd_path;//

	char	*cur_path;
	char	*line;
}				t_minfo;


//get_info.c
int		get_info(char **av, char **env, t_minfo *info);
int		copy_env(char **env, t_minfo *info);

//get_cmd_path.c
int		handle_env_path(t_minfo *info);
char	*ck_cmd(t_minfo *info);
void	add_cmd(char *pre, char *cmd, char **path);


//handle_buildin_cmd.c 
int		buitin_cmd_echo(t_minfo *info);
int		buitin_cmd_cd(t_minfo *info);

//handle_env.c
int		buitin_cmd_setenv(t_minfo *info);
int		buitin_cmd_unsetenv(t_minfo *info);
void	buidin_setenv(t_minfo *info, const char *env_key, const char *env_value);
int		print_env(t_minfo *info);
int		buitin_cmd_env(t_minfo *info);

//helper.c
char	*ft_strcjoin(const char *a, const char *b, char c);
int		check_str(char *str, char c);

//minishell.c
int		minishell(t_minfo *info);
int		ck_buildin_cmd(t_minfo *info);
int		exc_command(t_minfo *info);
int		check_buildin(t_minfo *info);
int		get_cmd_path(t_minfo *info);

//free.c
void	deep_free(char **dst);
void	free_for_loop(t_minfo *info);
void	free_everything(t_minfo *info);

//parse_line.c
void	parse_line(t_minfo *info);
char	**handle_qoated(char *line);

//handle_quotes.c
void	change_space(char *line);
void	cut_quos_refill_space(char **av);
int		line_wordcount(char *str);
char	**line_split(char const *s);

#endif

// this is  some   test with "quoted text  nside it"   blablabla
// 00this0is00some000test0with0"quoted text  nside it"000blablabla

// ~ -> 
// echo ~	
//c == ' ' || line[i] == '\t' || line[i] == '\v' || line[i] == '\r'