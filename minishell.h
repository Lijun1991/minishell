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

typedef struct	s_minfo
{
	char	**env;
	char	**cmd_env;
	char	*home;
	char	*env_path;
	char	**pre_path;

	char	**av;
	char	*cmd;
	char	*cmd_path;

	char	*line;
	int		sign;
}				t_minfo;

/*
** get_info.c
*/
int				get_info(char **av, char **env, t_minfo *info);
int				copy_env(char **env, t_minfo *info);
int				handle_env_path(t_minfo *info);

/*
** get_cmd_path.c
*/
void			check_dollor_sign(char **str, t_minfo *info);
char			*ck_cmd(t_minfo *info);
void			add_cmd(char *pre, char *cmd, char **path);
int				get_cmd_path(t_minfo *info);

/*
** handle_buildin_cmd.c
*/
int				buitin_cmd_echo(t_minfo *info);
int				buitin_cmd_cd(t_minfo *info);
int				buitin_cmd_unsetenv(t_minfo *info);
int				buitin_cmd_setenv(t_minfo *info);
int				buitin_cmd_env(t_minfo *info);

/*
** handle_env.c
*/
int				handle_executable_file(t_minfo *info, int len);
int				get_cmd_env(t_minfo *info, int len);
void			buitin_setenv(t_minfo *info, const char *env_key, \
	const char *env_value);

/*
** helper.c
*/
char			*ft_strcjoin(const char *a, const char *b, char c);
int				check_str(char *str, char c);
void			recheck_env_path(t_minfo *info);
int				print_env(t_minfo *info);
int				get_len(char **s);

/*
** minishell.c
*/
int				minishell(t_minfo *info);
int				exc_command(t_minfo *info);

/*
** free.c
*/
void			deep_free(char **dst);
void			free_for_loop(t_minfo *info);
void			free_everything(t_minfo *info);

/*
** parse_line.c
*/
int				parse_line(t_minfo *info);

/*
** prompt.c
*/
void			handle_prompt(int sign, t_minfo *info);

/*
** handle_quotes.c
*/
void			change_space(char *line);
void			cut_quos_refill_space(char **av);
char			**line_split(char const *s);

#endif
