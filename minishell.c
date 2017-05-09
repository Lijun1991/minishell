/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:32:13 by lwang             #+#    #+#             */
/*   Updated: 2017/05/08 00:36:00 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parse input in commands i.e. use gnl -- CHECK FOR ERRORS, NOT SEGFAULT OR LEAK!!!
//Check if commands if a buitin i.e echo, cd, setenv, unsetenv, env or exit
//if not, check if is in the PATH, before fork, check for access
//	then fork, parent waits, child execve
//if not, display error
//cleanup memory


int		ck_buildin_cmd(t_minfo *info)
{
	if (!ft_strcmp(info->cmd, "echo"))
		buitin_cmd_echo(info);
	else if (!ft_strcmp(info->cmd, "cd"))
		buitin_cmd_cd(info);
	else if (!ft_strcmp(info->cmd, "setenv"))
		buitin_cmd_setenv(info);
	else if (!ft_strcmp(info->cmd, "unsetenv"))
		;
	else if (!ft_strcmp(info->cmd, "env"))
		;
	else
		return (0);
	return (1); 
}

int		minishell(t_minfo *info)
{
	pid_t	pid;
	int		r;

	r = -10;
	while (1)
	{
		ft_printf("$>");
		get_next_line(0, &info->line);
		parse_line(info);
		// ft_printf("line is %s\n", info->av[1]);
		if (ck_buildin_cmd(info))
			;
		else if (info->cmd_path)
		{
			pid = fork();
			if (pid == 0)
			{
				// ft_printf("hello\n");
				execve(info->cmd_path, info->av, info->env);
				exit(1);
				// printf("Something terrible happened.\n");
				return (r);
			}
			else if (pid > 0)
			{
				wait(&r);
			}
			else
			{
				ft_printf("Rest in peace.\n");
				exit (1);
			}
		}
		else if (!ft_strncmp(info->cmd, "exit ", 4))
		{
			free_for_loop(info);
			return (0);
		}
		else
			ft_printf("wrong commmands\n");
		free_for_loop(info);
	}
	return (0);
}
