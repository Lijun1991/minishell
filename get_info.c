/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:46:29 by lwang             #+#    #+#             */
/*   Updated: 2017/05/08 00:30:31 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		copy_env(char **env, t_minfo *info)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(info->env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (1);
	i = 0;
	while (env[i])
	{
		info->env[i] = ft_strdup(env[i]);//..
		i++;
	}
	info->env[i] = NULL;
	return (0);
}

void	add_cmd(char *pre, char *cmd, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(pre, "/");
	*path = ft_strjoin(tmp, cmd);
	free(tmp);
}

void	ck_cmd(t_minfo *info)
{
	struct stat	sb;
	int			i;
	char		*new_path;

	i = 0;
	while (info->pre_path[i])
	{
		add_cmd(info->pre_path[i], info->cmd, &new_path);
		if (stat(new_path, &sb) != -1)
			info->cmd_path = ft_strdup(new_path);
		free(new_path);
		i++;
	}
}

void	handle_env_path(t_minfo *info)
{
	int		i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PATH", 4))
			info->env_path = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 5));//..
		if (!ft_strncmp(info->env[i], "HOME", 4))
			info->home = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 5));//..
		i++;
	}
	info->pre_path = ft_strsplit(info->env_path, ':');//..
}


int		get_info(int ac, char **av, char **env, t_minfo *info)
{

	if (!info)
		return (1);
	info->ac = ac;
	if (copy_env(env, info))
		return (1);
	if (av)
		;
	if (env && info->env)
		handle_env_path(info);
	else
		return (1);
	return (0);
}

