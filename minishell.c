/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:32:13 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 21:21:36 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parse input in commands i.e. use gnl -- CHECK FOR ERRORS, NOT SEGFAULT OR LEAK!!!
//Check if commands if a buitin i.e echo, cd, setenv, unsetenv, env or exit
//if not, check if is in the PATH, before fork, check for access
//	then fork, parent waits, child execve
//if not, display error
//cleanup memory


char	*ck_buildin_cmd(t_minfo *info)
{
	if (!ft_strcmp(info->cmd, "echo"))
		info->bcmd = ft_strdup("echo");//...
	else if (!ft_strcmp(info->cmd, "cd"))
		info->bcmd = ft_strdup("cd");//..
	else if (!ft_strcmp(info->cmd, "setenv"))
		info->bcmd = ft_strdup("setenv");//..
	else if (!ft_strcmp(info->cmd, "unsetenv"))
		info->bcmd = ft_strdup("unsetenv");//..
	else if (!ft_strcmp(info->cmd, "env"))
		info->bcmd = ft_strdup("env");//..
	else
		return (NULL);
	return (info->bcmd); 
}

int		minishell(t_minfo *info)
{
	pid_t	pid;
	int		r;

	r = -10;
	if (!ft_strncmp(info->cmd, "exit", 4))
		exit(1);
	while(ft_strncmp(info->cmd, "exit", 4))
	{
		if (ck_buildin_cmd(info))
			printf("print buildin cmd\n");
		else if (info->cmd_path)
		{
			ft_printf("$> %s\n", info->cmd);
			pid = fork();
			if (pid == 0)
			{
				execve(info->cmd_path, info->av, info->env);
				// printf("Something terrible happened.\n");
				return (r);
			}
			else if (pid > 0)
			{
				wait(&r);
				break ;
			}
			else
			{
				ft_printf("Rest in peace.\n");
				exit (1);
			}
		}
		else
			ft_printf("wrong commmands");
	}
	return (0);
}
