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

int		check_buildin(t_minfo *info)
{
	return (!ft_strcmp(info->cmd, "echo") || !ft_strcmp(info->cmd, "cd") ||
		!ft_strcmp(info->cmd, "setenv") || !ft_strcmp(info->cmd, "unsetenv") ||
		!ft_strcmp(info->cmd, "env") || !ft_strcmp(info->cmd, "exit"));
}

int		ck_buildin_cmd(t_minfo *info)
{
	if (!ft_strcmp(info->cmd, "echo"))
		return (buitin_cmd_echo(info));
	else if (!ft_strcmp(info->cmd, "cd"))
		return (buitin_cmd_cd(info));
	else if (!ft_strcmp(info->cmd, "setenv"))
		return (buitin_cmd_setenv(info));
	else if (!ft_strcmp(info->cmd, "unsetenv"))
		return (buitin_cmd_unsetenv(info));
	else if (!ft_strcmp(info->cmd, "env"))
		return (buitin_cmd_env(info));
	else if (!ft_strcmp(info->cmd, "exit"))
	{
		free_everything(info);
		exit(0);
	}
	return (0);
}

int		exc_command(t_minfo *info)
{
	pid_t	pid;
	int		r;

	r = -10;
	pid = fork();
	if (pid == 0)
	{
		// ft_printf("cmd_path is %s\n", info->cmd_path);
		execve(info->cmd_path, info->av, info->cmd_env ? info->cmd_env : info->env);
		exit(1);
	}
	else if (pid > 0)
	{
		wait(&r);
		if (r)
			ft_printf("cmd doesn't execve successfully\n");
	}
	else
	{
		ft_printf("Failed to fork process\n");
		exit (1);
	}
	return (r);
}

int		get_cmd_path(t_minfo *info)
{
	int	err;

	err = 0;
	if (access(info->cmd, X_OK) && info->env && !(err = handle_env_path(info)))
	{
		// ft_printf("hello1");
		if (!ck_cmd(info))
			return (0);
	}
	else if (!(err = access(info->cmd, X_OK)))
	{
		// ft_printf("hello2");
		info->cmd_path = ft_strdup(info->cmd);
		return (0);
	}
	else
		return (1);
	return (err);
}

int		minishell(t_minfo *info)
{
	int	sign;

	sign = 0;
	while (1)
	{
		if (sign)
			ft_printf(RED"$>"CLN);
		else
			ft_printf("$>");
		sign = 0;
		if (!get_next_line(0, &info->line))
			break ;
		parse_line(info);
		if (check_buildin(info))
		{
			if (ck_buildin_cmd(info))
				sign = 1;
		}
		else if (!get_cmd_path(info))
		{
			if (exc_command(info))
				sign = 1;
		}
		else
			ft_fprintf(2, "minishell: commmand not found: %s\n", info->cmd);
		free_for_loop(info);
	}
	return (0);
}





