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
		execve(info->cmd_path, info->cmd_env ? info->cmd_env : info->av, info->cmd_env ? info->cmd_env : info->env);
		exit(1);
	}
	else if (pid > 0)
	{
		wait(&r);
		// if (r)
		// 	ft_printf("cmd doesn't execve successfully\n");
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

	//CHECK if info->cmd contains / then call the appropriate function
	//otherwise do this:
	err = 0;
	if (ft_strchr(info->cmd, '/') )
	{
		info->cmd_path = ft_strdup(info->cmd);
		if (!access(info->cmd_path, X_OK))
			return (0);
		else
		{
			ft_fprintf(2, "minishell: permission denied: %s\n", info->cmd);
			return (0);
		}
	}
	else if (info->env && !(err = handle_env_path(info)))
	{
		if (ck_cmd(info) != NULL)
			return (0);
		else
			return (1);
	}
	else
		return (1);
	return (err);
}

void	handle_prompt(int sign, t_minfo *info)
{
	char	buf[MAX_PATH_LENGTH + 1];
	char	*pwd;

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	if (sign)
	{
		if (!ft_strcmp(pwd, info->home))
			ft_printf(RED"$~"CLN);
		else
			ft_printf(RED"$>"CLN);
	}
	else
	{
		if (!ft_strcmp(pwd, info->home))
			ft_printf("$~");
		else
			ft_printf("$>");
	}
}

int		run_command(t_minfo *info)
{
	if (check_buildin(info))
	{
		if (ck_buildin_cmd(info))
			info->sign = 1;
	}
	else if (!ft_strcmp(info->cmd, ""))
		info->sign = 0;
	else if (!get_cmd_path(info))
	{
		if (exc_command(info))
			info->sign = 1;
	}
	else
	{
		ft_fprintf(2, "minishell: commmand not found: %s\n", info->cmd);
		info->sign = 1;
	}
	return (0);
}

int		minishell(t_minfo *info)
{
	while (1)
	{
		handle_prompt(info->sign, info);
		info->sign = 0;
		if (!get_next_line(0, &info->line))
			break ;
		if (!(parse_line(info)))
			run_command(info);
		else
		{
			ft_fprintf(2, "None support\n");
			info->sign = 1;
		}
		free_for_loop(info);
		handle_env_path(info);
	}
	return (0);
}





