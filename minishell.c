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
		wait(&r);
	else
	{
		ft_printf("Failed to fork process\n");
		exit (1);
	}
	return (r);
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
		recheck_env_path(info);
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
	}
	return (0);
}





